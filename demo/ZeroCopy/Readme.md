This demo showcases the deployment of SWIFT DDS to send and receive data through ZeroCopy using a simple datatype named *ZeroCopy*. This datatype, defined in *ZeroCopy.idl*, comprises unsigned short, unsigned long, and char array types.

Follow the steps below to run this demo. Cmake with version equal or greater than 3.5 is required.

**Step 1**: Run the following commands to compile the project. Set ***TARGET_OS*** by adding *'-D TARGET_OS=<target_os>'* when executing *'cmake ..'* accroding the platform. There are four available values for ***TARGET_OS***, which correspond to different platforms: **LINUX_X86_18 (default)**, **LINUX_X86_20**, **LINUX_X86_22**, **LINUX_X86_24**, and **LINUX_ARM**. Upon successful compilation, an executable file named *TestZeroCopy* will be generated.

> mkdir build  
> cd build  
> cmake ..  
> make -j8  
> cd ..

**Step 2**: Modify the *config.json* file by filling ***local_host*** and ***transport_locator_list*** with the IP address that will be used for the communication. Port number is optional. Additionly, ensure that the ***domain_id*** is set to the same value for all the participants involved in the communication. 

In order to use ZeroCopy communication mode, please set ***only_recv_by_udp*** to **false** , SHM is ranked first in the ***prefer_transport_kind*** list, and ***enableZeroCopy*** to **true** in both writer and reader's configuration. The pre-allocated memory size can also be adjusted by modifying ***zeroCopyMemorySize***, which is set to **104857600** by default.

**Step 3**: Create a publisher and a subscriber to achieve communication.  

Specify the ***LD_LIBRARY_PATH*** environment variable to include the directory where the corresponding dynamic library of SWIFT DDS is located.
> export LD_LIBRARY_PATH=<library_path>:$LD_LIBRARY_PATH

For sender:
> ./TestZeroCopy -n pub

For receiver:  
> ./TestZeroCopy -n sub

The full command options can be checked by:
> ./TestZeroCopy -h

Matching messages will be printed on the screen if sender and receiver match each other successfully. Otherwise, please double check IP address and domain_id. 

If still unmatched, please try the following command to manually manipulate the network routing table:
> route add -net 224.0.0.0 netmask 240.0.0.0 <network_adapter_name>