#ifndef _database_h
#define _database_h
    #include <string>
    #include <fstream>
    //宏定义
    #define OK 0
    #define ERROR -1
    //创建用户
    //用户数据以txt文档形式储存
    namespace Data_Base{
        std::string tip();

        typedef class user{
        private:
            std::string username; 
            int password;
        public:
            //构造函数        
            user(){
                username = '0'; //用户名
                password = 0; //密码
            }        
            inline bool search(std::string File_name){
                std::ifstream fin(File_name);
                if (!fin){                 //判断用户是否存在
                    return true;
                }
                else{
                    return false;
                }
            }                
            int change(class user *c); //修改用户数据
            int Delete(class user *d);  //删除
            int creat(class user *Creat); //创建

        }user;
        //数据
        typedef class database{
            private:            
                database *NeXt; //链表指针
                std::string name; //数据名
                int number; //数据号
                const std::string data_exit = "data-exit"; 
                const std::string data_delete = "data-delete";
                const std::string data_add = "data-add";
                const std::string find_d = "data-find";
                const std::string Prints ="print";                
            public:    
                int size;
                database() = default;            
                int Delete(class database *Del); //删除数据
                int Search(class database *find_end); //查找
                int add(class database *add); //插入
                int fileread(database *init);
                int print_to_file(database *printtofile,std::string Filename);
                int print_to_screen(database *prints);
        }database;
//命令行
        typedef class Command{
            private:                
                const std::string Help = "help";
                const std::string ChanGe ="change";
                const std::string Delete = "delete"; //几个关键词
                const std::string CrEat = "creat";
                const std::string Find = "find";    
                const std::string sudo = "sudo" ;
                const std::string login = "login";
                const std::string exit = "exit";
            public:
                Command() = default;
                void help();        //帮助
                int comander(Command *c,user *u,database *data); //命令行
        }Command;
    //帮助
        void Command::help(){
            std::cout<<"help"<<"\n";
            std::cout<<"1.press /help/ to see how to use"<<"\n"; //OK
            std::cout<<"2.press /change/ to change meeage"<<"\n"; //OK
            std::cout<<"3.press /delete/ to delete a dataline"<<"\n"; //OK
            std::cout<<"4.press /creat/ to creat a dataline"<<"\n"; //OK
            std::cout<<"5.press /login/ to login the dataline"<<"\n"; //OK
            std::cout<<"7.press /data-find/ to find the data"<<"\n";    //OK
            std::cout<<"8.press /data-exit/ to exit the dataline"<<"\n"; //OK
            std::cout<<"9.press /data-delete/ to delete the data in dataline"<<"\n"; //OK
            std::cout<<"10.press /data-add/ to add the data in dataline"<<"\n";//OK
            std::cout<<"11.press /exit/ to exit the program"<<"\n";//OK
            std::cout<<"12.press /print/ to show the data in the dataline"<<"\n";
        }
    //命令行
        int Command::comander(class Command *c,class user *u,class database *data){
            std::cout<<"Welcome to use Small database!"<<"\n";
            while (true){
                std::string command;
                std::cout<<"database->$:";
                std::cin>>command; //读入命令
                if (command == c->Help){
                c->help(); //帮助
                }
                else if (command == c->CrEat){
                    u->creat(u); //创建用户
                }
                else if (command == c->Delete){
                    u->Delete(u); //删除数据
                }
                else if (command == c->ChanGe){
                    u->change(u); //修改用户数据
                }
                else if (command == c->Find){
                    std::string filename; //查找数据·
                    std::cout<<"Search"<<"\n"<<"what you want to Search?"<<"\n"<<"input dataline's name:";
                    std::cin>>filename;
                    u->search(filename);
                }
                else if (command == c->login){
                    data->fileread(data);
                }    
                else if (command == c->exit){
                    return OK;
                }
               else{
                    std::cout<<"Command is not found!"<<"\n";
                }
            }
            return OK;
        }
    }
#endif
