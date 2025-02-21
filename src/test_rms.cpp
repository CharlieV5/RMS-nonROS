#include <rms/rms.h>
#include <string>
#include <pcl/io/pcd_io.h>

void main(int argc, char **argv)
{
  if (argc == 2)
  {
    std::string filename = argv[1];
    pcl::PointCloud<pcl::PointXYZ>::Ptr cloud(new pcl::PointCloud<pcl::PointXYZ>);
    pcl::io::loadPCDFile(filename, *cloud);
    rms::RMS rms(10, 0.00004f, 0.2f, 0.2f);
    rms.sample(cloud);

    pcl::io::savePCDFile("rms.pcd", *cloud);
  }
}