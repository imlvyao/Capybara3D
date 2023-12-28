//#include <boost/interprocess/managed_shared_memory.hpp>
//#include <boost/archive/binary_oarchive.hpp>
//#include <boost/interprocess/containers/string.hpp>
//#include <boost/serialization/vector.hpp>
//#include <boost/interprocess/containers/vector.hpp>
//#include <iostream>

// 互斥量用于保护共享内存的访问
//boost::interprocess::interprocess_mutex mutex;

//void writeSharedMemory(const char* message) {
//    using namespace boost::interprocess;
//
//    try {
//        // 打开共享内存对象
//        shared_memory_object sharedMemory(open_only, "MySharedMemory", read_write);
//
//        // 映射共享内存到进程地址空间
//        mapped_region region(sharedMemory, read_write);
//
//        // 获取共享内存的起始地址
//        void* sharedMemoryAddress = region.get_address();
//
//        // 锁定互斥量，确保线程安全访问共享内存
//        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(mutex);
//
//        // 在共享内存中写入数据
//        std::strcpy(static_cast<char*>(sharedMemoryAddress), message);
//    }
//    catch (const std::exception& e) {
//        std::cerr << "Error: " << e.what() << std::endl;
//    }
//}
//
//void readSharedMemory() {
//    using namespace boost::interprocess;
//
//    try {
//        // 打开共享内存对象
//        shared_memory_object sharedMemory(open_only, "MySharedMemory", read_only);
//
//        // 映射共享内存到进程地址空间
//        mapped_region region(sharedMemory, read_only);
//
//        // 获取共享内存的起始地址
//        void* sharedMemoryAddress = region.get_address();
//
//        // 锁定互斥量，确保线程安全访问共享内存
//        boost::interprocess::scoped_lock<boost::interprocess::interprocess_mutex> lock(mutex);
//
//        // 从共享内存中读取数据
//        std::cout << "Message from shared memory: " << static_cast<const char*>(sharedMemoryAddress) << std::endl;
//    }
//    catch (const std::exception& e) {
//        std::cerr << "Error: " << e.what() << std::endl;
//    }
//}
//
//int main() {
//    // 创建共享内存对象
//    boost::interprocess::shared_memory_object sharedMemory(
//        boost::interprocess::open_or_create, "MySharedMemory", boost::interprocess::read_write);
//
//    // 设置共享内存大小为100字节
//    sharedMemory.truncate(100);
//
//    // 启动一个写线程
//    boost::thread writerThread(writeSharedMemory, "Hello, Boost Shared Memory!");
//
//    // 启动一个读线程
//    //boost::thread readerThread(readSharedMemory);
//
//    // 等待线程结束
//    writerThread.join();
//    //readerThread.join();
//    system("pause");
//    return 0;
//}

#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <boost/serialization/vector.hpp>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/allocators/allocator.hpp>  
#include <boost/interprocess/sync/named_mutex.hpp>
#include <boost/interprocess/sync/scoped_lock.hpp>
#include <iostream>
#include <string>
#include "ToppleTheTower/Actor.h"

boost::interprocess::interprocess_mutex mutex;
using namespace boost::interprocess;


int main()
{
    const char* sharedMemoryName = "MySharedMemory";
    const char* mutexName = "MyMutex";
    const std::size_t sharedMemorySize = 65536; // Adjust the size according to your needs
    double ra = 0;
    while (true)
    {
        try {
            boost::interprocess::named_mutex::remove(mutexName);
            boost::interprocess::named_mutex namedMutex(boost::interprocess::open_or_create, mutexName);
            boost::interprocess::scoped_lock<boost::interprocess::named_mutex> lock(namedMutex);

            boost::interprocess::shared_memory_object::remove(sharedMemoryName);
            // Create or open the managed shared memory
            boost::interprocess::managed_shared_memory segment(
                boost::interprocess::open_or_create, sharedMemoryName, sharedMemorySize);

            // Serialize the MyData object to a stringstream
            //MyData myDataObject;
            //myDataObject.intValue = 42;
            //myDataObject.doubleValue = 3.14;
            //myDataObject.stringValue = "Boost.Serialization is cool!";
            //myDataObject.vec= { 1, 2, 3, 4, 5 };

            TransData myDataObject;

            myDataObject.m_canvas = Canvas(0, 100, 100, 160);
            myDataObject.m_enemy.getTower().push_back(Tower(0, 80, 20, 40));
            myDataObject.m_enemy.getFootman().push_back(Footman(-50, 50+sin(ra)*10, 10, 15));
            myDataObject.m_enemy.getFootman().push_back(Footman(50, 60, 10, 15));

            myDataObject.m_self.getTower().push_back(Tower(0, -80, 20, 40));
            myDataObject.m_self.getFootman().push_back(Footman(-50, -50, 10, 15));
            myDataObject.m_self.getFootman().push_back(Footman(50, -60 + sin(ra) * 10, 10, 15));

            std::stringstream ss;
            //boost::archive::text_oarchive oa(ss);
            boost::archive::binary_oarchive oa(ss);
            oa << myDataObject;

            // Get the serialized data from the stringstream
            std::string serializedData = ss.str();

            // Allocate a buffer in shared memory to store the serialized data
            char* sharedMemoryBuffer = segment.construct<char>("SharedMemoryBuffer")[serializedData.size()]();

            // Copy the serialized data to the shared memory buffer
            std::copy(serializedData.begin(), serializedData.end(), sharedMemoryBuffer);

        }
        catch (const std::exception& e) {
            std::cerr << "Exception: " << e.what() << std::endl;
        }
        Sleep(1);
        ra += 0.1;
    }
    // The shared memory will be automatically released when all processes are done

    return 0;
}
