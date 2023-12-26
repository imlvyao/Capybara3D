#include <boost/interprocess/managed_shared_memory.hpp>
#include <boost/interprocess/allocators/allocator.hpp>
#include <boost/interprocess/containers/vector.hpp>
#include <boost/interprocess/containers/string.hpp>
#include <iostream>

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

#include "ToppleTheTower/Actor.h"

boost::interprocess::interprocess_mutex mutex;
using namespace boost::interprocess;
int main() 
{
    boost::interprocess::shared_memory_object::remove("SharedMemory");
    // 定义数据
    boost::interprocess::managed_shared_memory segment(boost::interprocess::open_or_create, "SharedMemory", 65536);

    typedef boost::interprocess::allocator<Tower, boost::interprocess::managed_shared_memory::segment_manager> TowerAllocator;
    typedef boost::interprocess::vector<Tower, TowerAllocator> SharedTowerVector;

    typedef boost::interprocess::allocator<Footman, boost::interprocess::managed_shared_memory::segment_manager> FootmanAllocator;
    typedef boost::interprocess::vector<Footman, FootmanAllocator> SharedFootmanVector;

    TransData* data = segment.construct<TransData>("TransData")();

    data->m_canvas = Canvas(0, 100, 100, 160);
    data->m_enemy.getTower().push_back(Tower(0, 80, 20, 40));
    data->m_enemy.getFootman().push_back(Footman(-50, 50, 10, 15));
    data->m_enemy.getFootman().push_back(Footman(50, 60, 10, 15));

    data->m_self.getTower().push_back(Tower(0, -80, 20, 40));
    data->m_self.getFootman().push_back(Footman(-50, -50, 10, 15));
    data->m_self.getFootman().push_back(Footman(50, -60, 10, 15));

    // Access shared memory allocators
    TowerAllocator towerAllocator(segment.get_segment_manager());
    FootmanAllocator footmanAllocator(segment.get_segment_manager());

    // Create shared memory vectors for Enemy and Self
    SharedTowerVector* sharedEnemyTowerVector = segment.construct<SharedTowerVector>("SharedEnemyTowerVector")(towerAllocator);
    SharedFootmanVector* sharedEnemyFootmanVector = segment.construct<SharedFootmanVector>("SharedEnemyFootmanVector")(footmanAllocator);
    SharedTowerVector* sharedSelfTowerVector = segment.construct<SharedTowerVector>("SharedSelfTowerVector")(towerAllocator);
    SharedFootmanVector* sharedSelfFootmanVector = segment.construct<SharedFootmanVector>("SharedSelfFootmanVector")(footmanAllocator);

    // Copy data from the original vectors to shared memory vectors
    std::copy(data->m_enemy.getTower().begin(), data->m_enemy.getTower().end(), std::back_inserter(*sharedEnemyTowerVector));
    std::copy(data->m_enemy.getFootman().begin(), data->m_enemy.getFootman().end(), std::back_inserter(*sharedEnemyFootmanVector));
    std::copy(data->m_self.getTower().begin(), data->m_self.getTower().end(), std::back_inserter(*sharedSelfTowerVector));
    std::copy(data->m_self.getFootman().begin(), data->m_self.getFootman().end(), std::back_inserter(*sharedSelfFootmanVector));

    std::cout << "Data sent to shared memory." << std::endl;
}
