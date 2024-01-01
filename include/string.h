#ifndef STRUCTSPP_PROJECT_STRING_H
#define STRUCTSPP_PROJECT_STRING_H
#include <cstring>
#include <string>
#include <iostream>
#include <vector>
#include "file.h"

namespace utils{
    class string{
    protected:
        size_t _long = 10;
        char *s=new char[_long];
        size_t _length=0;
        void flash_size(size_t newsize){
            char *c = s;
            delete []s;
            s = new char[newsize];
            strcpy(s, c);
            _long = newsize;
            delete []c;
        }
        void flash(size_t newsize, const char* newstr){
            flash_size(strlen(newstr)+1);
            strcpy(s, newstr);
            this->_length = strlen(newstr);
        }
        friend class file;
    public:
        const char* begin() const {
            return s;
        }
        const char* end() const {
            return s + _length;
        }
        char* begin() {
            return s;
        }
        char* end() {
            return s + _length;
        }
        size_t strlen(){
            size_t i=0;
            while(s[i]!='\0')i++;
            return i;
        }
        static size_t strlen(const char *c){
            size_t i = 0;
            while (c[i]!='\0')i++;
            return i;
        }
        string():_length(0){}
        string(const char* c){
            flash(string::strlen(c)+1, c);
        }
        void operator=(string str){
            flash(str._long, str.s);
        }
        char operator[](size_t i){
            return this->s[i];
        }
        bool operator==(string str){
            return stramt(str);
        }
        bool operator!=(string str){
            return !stramt(str);
        }
        void strcpyto(string t){
            t.flash(this->_long, this->s);
        }
        void strcpyto(char* &t){
            t = this->s;
        }
        void strcpyto(std::string& t){
            t = s;
        }
        void strcpyin(string f){
            this->flash(f._long, f.s);
            this->_length = f._length;
        }
        template <size_t size>
        void strcpyin(char (*f)[size]){
            this->flash(size, f);
            this->_length = size;
        }
        void strcpyin(std::string f){
            this->flash(f.size(), f.c_str());
            this->_length = f.length();
        }
        //todo make two functions can Accepts two arbitrary one-dimensional character arrays ，name strcpyin and strcpyout.
        char* c_str(){
            return s;
        }
        bool empty(){
            if (_length == 0) return true;
            return false;
        }
        void clear(){
            s = NULL;
            this->_length = 0;
        }
        char* data(){
            return s;
        }
        void push_back(char c){
            this->flash(this->_long+1, this->s+c);
        }
        bool substr(string sub){
            return strstr(this->s, sub.s);
        }
        bool substr(char* sub){
            return strstr(this->s, sub);
        }
        bool substr(const char* sub){
            return strstr(this->s, sub);
        }
        friend bool substr(char* str, string sub){
            return strstr(str, sub.s);
        }
        friend bool substr(const char* str, string sub){
            return strstr(str, sub.s);
        }
        bool stramt(string str){
            return strcmp(str.s, this->s);
        }
        size_t size(){
            return _length;
        }
        size_t length() {
            return this->size();
        }
        ~string(){
            delete[] s;
        }
        operator int(){
            return std::stoi(s);
        }
        operator long(){
            return std::stol(s);
        }
        operator double(){
            return std::stod(s);
        }
        operator float(){
            return std::stof(s);
        }
        operator long long(){
            return std::stoll(s);
        }
        operator unsigned long(){
            return std::stoul(s);
        }
        operator unsigned long long (){
            return std::stoull(s);
        }
        operator char*(){
            return this->c_str();
        }
        operator std::string(){
            return std::string(s);
        }
        string operator+(string l){
            string ret;
            ret._long = this->_long + l._long;
            ret._length = this->_length + l._length;
            ret.s = new char[ret._long];
            strcpy(ret.s, strcat(this->s, l.s));
        }
        friend void operator<<(std::ostream &out, string str){
            out << str.s;
        }
        friend std::istream& operator>>(std::istream& in, string& str) {
            std::vector<char> temp;
            char ch;
            while (in.get(ch) && ch != '\n') {
                temp.push_back(ch);
            }
            temp.push_back('\0');
            str.flash_size(temp.size());
            std::copy(temp.begin(), temp.end(), str.s);
            str._length = temp.size() - 1;
            return in;
        }
    };
}
#endif //STRUCTSPP_PROJECT_STRING_H
