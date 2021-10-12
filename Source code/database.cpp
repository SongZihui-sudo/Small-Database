#include <iostream>
#include <fstream>
#include <string>
#include "database.h"

using namespace Data_Base;

//主函数
int main(){   
    Command *co;
    user *USER;
    database *Data;
    USER = new(user); //用户命令行交互
    co = new(Command);
    Data = new(database);
    co->comander(co,USER,Data);
}
//创建用户
int user::creat(class user *Creat){
    std::string filename;
    std::cout<<"Let's start! Creat a new database user!"<<"\n"<<"input dataline's name:";
    std::cin>>filename;
    std::ofstream fout(filename); //创建相关txt文件
    if (fout){ 
        std::cout<<"input username:";
        std::cin>> Creat->username; //读入用户名
        fout<<Creat->username<<std::endl; 
        std::cin.ignore(100,'\n'); //清空输入缓冲区
        std::cout<<"input password:";
        std::cin>>Creat->password; //读入密码
        fout<<Creat->password<<std::endl;
    }
    fout.close(); //关闭文件
    return OK;
}
//删除
int user::Delete(class user *d){
    std::cout<<"Delete"<<"\n"<<"what you want to Delete?"<<"\n"<<"input dataline's name:";
    std::string filename;
    std::cin>>filename; 
    const char* file_name;
    file_name = filename.c_str(); 
    if (d->search(filename)){ //读入数据链名判断是否存在，存在则调用remove删除
        if (std::remove(file_name) == 0){
            std::cout<<"delete successful"<<"\n";
            return OK; //删除成功
        }
        else{
            std::cout<<"delete false!"<<"\n";
            return ERROR; //删除失败
        } 
    }
    else{
        std::cout<<"not found!"<<"\n";
        return ERROR; //没找到相关文件
    }
    return OK;
}
//修改
int user::change(class user *c){
    std::cout<<"Change"<<"\n"<<"what you want to Change?"<<"\n"<<"input dataline's name:";
    std::string filename;
    std::cin>>filename;
    std::ofstream fout(filename); //创建相关txt文件
    if (c->search(filename)){
        std::cout<<"not find!"<<std::endl;
        return ERROR; //没找都相关文件 
    }
    else{
        std::cout<<"input username:";
        std::cin>> c->username; //读入用户名
        fout<<c->username<<std::endl; 
        std::cin.ignore(100,'\n'); //清空输入缓冲区
        std::cout<<"input password:";
        std::cin>>c->password; //读入密码
        fout<<c->password<<std::endl;
    }
    fout.close(); //关闭文件
        return OK;
    }
//从用户文件中读取数据并存入链表中
int database::fileread(class database *init){
    user *file_user;
    database *head; //定义头节点和中间节点
    database *node;
    database *end;
    head = new(database);
    end = new(database);
    head -> NeXt = end ;
    end = head;
    head ->name = '0';  //初始化
    head ->number = 0;
    //提示
    std::cout<<"Read the data"<<"\n"<<"what you want to read?"<<"\n"<<"input dataline's name:";
    std::string filename;        //读取数据链名
    std::string UserName;
    int PassWord;
    std::cin>>filename;
    std::cin.ignore(100,'\n');
    std::cout<<"input username:";
    std::string user_name;
    std::cin>>user_name;  //输入用户名和密码
    std::cout<<"input password:";
    int pass_word;
    std::cin>>pass_word;
    if (file_user->search(filename)){ //判断文件是否存在
        std::cout<<"not find!"<<std::endl;
        file_user->creat(file_user);   //文件不存在，新建一个
        return ERROR; //没找都相关文件
    } 
    else{
        std::ifstream fin(filename);
        fin>>UserName>>PassWord; //链表的第一个节点存放用户信息
        head->name = UserName;
        head->number = PassWord;
        fin.close();
        std::ifstream openfile(filename.c_str());
        if(user_name == UserName && pass_word == PassWord){  //判断用户名与密码是否正确
            std::string line;
            int j =0;
            node = new(database);
            while(std::getline(openfile,line)){
                j++;                    
                if (j%2 == 0){
                    node->number = std::stoi(line); //读取数据编号                
                    node = new(database);
                    node->NeXt = end;
                    end = node;      //建表
                }
                else{
                    node->name = line;    //读入链表中数据名                
                }
            }
            fin.close();   //关闭文件
        }  
        else{
            std::cout<<"user or password is mistake!"<<std::endl;     //密码与用户名不对
            return ERROR;
        }   
            }   
        while (true){
            std::string com;
            std::cout<<"dataline->$:";
            std::cin>>com;
            if (com == init->find_d){
                init->Search(end); //在链表中搜索
            }
            else if (com == init->write){
                init->filewrite(); //写入数据
            }
            else if (com == init->data_exit){
                break; //退出登录
            }
            else if (com == init->data_add){
                init->add(init); //向链表添加数据
            }
            else if (com == init->data_change){
                init->Change(init); //修改数据
            }
            else if (com == init->data_delete){
                init->Delete(init); //删除数据
            }
            else{
                std::cout<<"Command is not found!"<<"\n"; //错误处理
            }
        }
    return OK; //返回OK
}
//在数据链中寻找数据
int database::Search(class database *find_end){
    char b;        
    std::string Data_Name;
    int data_number;         
    std::cout<<"find the data"<<"\n"<<"what you want to find?"<<"\n"<<"input n (name) or b (number):";
    if (b == 'n'){    
        std::cout<<"input data name:";
        std::cin>>Data_Name;       //读入要查的字符串
    }
    else if(b == 'b'){
        std::cout<<"input data number:";
        std::cin>>data_number;      //读入数字
    }
    else{
        std::cout<<"Command is not found!"<<"\n";
    }
    for (int i = 0; i < size+1; i++){    //通过暴力遍历法寻找数据
        std::cout<<"finding!"<<std::endl;
        if (Data_Name == find_end->name || data_number == find_end->number){
            std::cout<<"postion is"<<i<<std::endl;
        }
        find_end = find_end->NeXt; //遍历
    }
    return OK;
}

int database::add(class database *add){
    database *temp;
    temp = new(database);
    size++;
    temp = NULL;
    std::cout<<"input data name:"<<std::endl;
    std::cin>>temp->name;       //读入要添加的字符串
    std::cout<<"input number:"<<std::endl;
    std::cin>>temp->number; //读入要添加的数字
    temp->NeXt =add;
    add = temp;
    std::cout<<"input filename:"<<std::endl; //读入文件名
    std::string filename;
    std::cin>>filename;
    database::print_to_file(add,filename); //向用户文件中重新写入文件
    return OK;
}

int database::Change(class database *change){
    return OK;
}

int database::Delete(class database *Del){
    return OK;
}

int database::print_to_file(class database *print_to_file,std::string Filename){
    std::cout<<"print data to file!"<<std::endl;
    database *Positive_direction_node;
    database *Positive_direction_end;     //节点
    Positive_direction_node = new(database);
    Positive_direction_end = new(database); //分配内存空间
    std::fstream print_file(Filename);
    for (int i = 0; i < size+1; i++){
        print_to_file->name = Positive_direction_node->name;
        print_to_file->number = Positive_direction_node->number;
        Positive_direction_node->NeXt = Positive_direction_end; //重新建立一个保存数据的链表，方向是正向
        Positive_direction_end = Positive_direction_node;
        print_to_file = print_to_file->NeXt;
    }
    for (int i = 0; i < size+1; i++){
        print_file<<Positive_direction_end->name<<std::endl;
        print_file<<Positive_direction_end->number<<std::endl; //写入数据
        Positive_direction_end = Positive_direction_end->NeXt;
    }
    print_file.close();
    return OK;
}
//写入数据
int database::filewrite(){
    user file_user;
    std::cout<<"Write the data"<<"\n"<<"what you want to write?"<<"\n"<<"input dataline's name:";
    std::string filename;
    std::cin>>filename;     //读入文件名
    std::string user_name;
    int pass_word;
    std::cout<<"input username:";
    std::cin>>user_name;
    std::cout<<"input passsword:";
    std::cin>>pass_word;
    std::cin.ignore(100,'\n');
    if (file_user.search(filename)){
        std::cout<<"not find!"<<std::endl;
            return ERROR; //没找都相关文件 
            }
    else{
        std::ifstream fin(filename);
        std::fstream f;
        f.open(filename,std::ios::app);
        std::cin.ignore(100,'\n');
        std::cin>>size;
        std::string UserName;
        int PassWord;
        fin>>UserName>>PassWord; //读取用户名和密码
        std::cout<<"input size:";
        std::cin>>size;
        if(user_name == UserName && pass_word == PassWord){ //判断用户名与密码
            for ( int i = 0; i < size; i++){
                std::cout<<"input data name:";
                std::cin>>database::name;
                f<<database::name<<std::endl; //读入字符串
                std::cin.ignore(100,'\n');
                std::cout<<"input data number:";
                std::cin>>database::number; //读入数字
                f<<database::number<<std::endl;
                std::cin.ignore(100,'\n'); //清空缓冲区
            }
            f.close();
            return OK;
            }
        else{
            std::cout<<"user or password is mistake!"<<std::endl;     //密码与用户名不对
            return ERROR;
        }
    }
    return OK;
}
