Greenstone *idlparser* is a command line tool for generating SWIFT DDS Type and TopicDataType source code based on user-defined IDL(Interface Definition Language) file. The generated code can be included by SWIFT DDS applications to represent the datatype binding to a Topic.  

Follow the instructions below to generate datatype source code. Please make sure that user-defined IDL file conforms to official OMG(Object Management Group) standard *Interface Definition Language™ Version 4.2*. Both linux and win64 platformed *idlparser* are provided.  

Simple use case:
> ./idlparser HelloWorld.idl

Following messages will be printed on the screen if source codes are successfully generated.
> Generating Type Files......  
> Type Files generated successfully.  
> Generating TopicDataType Files......  
> TopicDataType Files generated successfully.  

And these source files will be present in the same folder: *Helloworld.cpp*, *Helloworld.h*, *HelloworldTopicDataType.cpp* and *HelloworldTopicDataType.h*.

Check the full command options by:
> ./idlparser -h
