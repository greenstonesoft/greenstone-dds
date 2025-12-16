This demo showcases the deployment of SWIFT DDS to enable data exchange through publication and subscription using a simple datatype named *Helloworld*. This datatype, defined in *Helloworld.idl*, comprises unsigned short, unsigned long, and string types.

Follow the steps below to run this demo. Cmake with version equal or greater than 3.5 is required.

**Step 1**: Run the following commands to compile the project. Set ***TARGET_OS*** by adding *'-D TARGET_OS=<target_os>'* when executing *'cmake ..'* accroding the platform. There are four available values for ***TARGET_OS***, which correspond to different platforms: **LINUX_X86_18 (default)**, **LINUX_X86_20**, **LINUX_X86_22**, **LINUX_X86_24**, and **LINUX_ARM**. Upon successful compilation, an executable file named *TestHelloworld* will be generated.

> mkdir build  
> cd build  
> cmake ..   
> make -j8  
> cd ..

**Step 2**: Modify the *config.json* file by filling ***local_host*** with the IP address that will be used for the communication. Port number is optional. Additionly, ensure that the ***domain_id*** is set to the same value for all the participants involved in the communication. 

To choose the communication mode, adjust the ***comm_kind*** and ***auto_op*** fields. For UDP, TCP and Shared Memory, set comm_kind to **1**, **4** and **16**, respectively. Setting ***auto_op*** to **true** means SWIFT DDS can automatically optimize the communication mode to Shared Memory if it detects that both publisher and subscriber are on the same machine, regardless of the ***comm_kind*** setting.

**Step 3**: Create a publisher and a subscriber to achieve communication.  

Specify the ***LD_LIBRARY_PATH*** environment variable to include the directory where the corresponding dynamic library of SWIFT DDS is located.
> export LD_LIBRARY_PATH=<library_path>:$LD_LIBRARY_PATH

For sender:
> ./TestHelloworld -n pub

For receiver:  
> ./TestHelloworld -n sub

The full command options can be checked by:
> ./TestHelloworld -h

Matching messages will be printed on the screen if sender and receiver match each other successfully. Otherwise, please double check IP address and domain_id. 

If still unmatched, please try the following command to manually manipulate the network routing table:
> route add -net 224.0.0.0 netmask 240.0.0.0 <network_adapter_name>
