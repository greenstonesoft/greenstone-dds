This demo showcases the method to test the network latency performance of Greenstone SWIFT DDS using a simple datatype named *Latency*. This datatype, defined in *Latency.idl*, comprises long and string types.

Follow the steps below to run this demo. Cmake with version equal or greater than 3.5 is required.

**Step 1**: Run the following commands to compile the project. Set ***TARGET_OS*** by adding *'-D TARGET_OS=<target_os>'* when executing *'cmake ..'* accroding the platform. There are four available values for ***TARGET_OS***, which correspond to different platforms: **LINUX_X86_18 (default)**, **LINUX_X86_20**, **LINUX_X86_22**, **LINUX_X86_24**, and **LINUX_ARM**. Upon successful compilation, an executable file named *Latency* will be generated.

> mkdir build  
> cd build  
> cmake ..   
> make -j8  
> cd ..

**Step 2**: Modify the *config.json* file by filling ***local_host*** with the IP address that will be used for the communication. Port number is optional. Additionly, ensure that the ***domain_id*** is set to the same value for all the participants involved in the communication. 

To choose the communication mode, adjust the ***comm_kind*** and ***auto_op*** fields. For UDP, TCP and Shared Memory, set comm_kind to **1**, **4** and **16**, respectively. Setting ***auto_op*** to **true** means SWIFT DDS can automatically optimize the communication mode to Shared Memory if it detects that both publisher and subscriber are on the same machine, regardless of the ***comm_kind*** setting.

Modify the *payload.txt* to test the network latency performance under varied settings of ***payload_size*** and ***payload_count***.

**Step 3**: Run latency test.  

Specify the ***LD_LIBRARY_PATH*** environment variable to include the directory where the corresponding dynamic library of SWIFT DDS is located.
> export LD_LIBRARY_PATH=<library_path>:$LD_LIBRARY_PATH

For sender:
> ./Latency -n pub

For receiver:  
> ./Latency -n sub

The full command options can be checked by:
> ./Latency -h

The test result will be presented in the format below including [Payload Size, Received Count, Loss Rate, Average, Maximum, Minimum, Median, Standard Deviation].  
> Payload:         16  B | Received:     500000 | Loss Rate:       0.00 % | latencyAvg:          6 us | latencyMax:          9 us | latencyMin:          6 us | latencyMed:          6 us | latencyStd:          9 us |  
> Payload:         32  B | Received:     500000 | Loss Rate:       0.00 % | latencyAvg:          6 us | latencyMax:          9 us | latencyMin:          6 us | latencyMed:          6 us | latencyStd:          7 us |

Matching messages will be printed on the screen if sender and receiver match each other successfully. Otherwise, please double check IP address and domain_id. 

If still unmatched, please try the following command to manually manipulate the network routing table:
> route add -net 224.0.0.0 netmask 240.0.0.0 <network_adapter_name>