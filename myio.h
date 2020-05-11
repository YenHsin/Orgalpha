#ifndef MYIO_H_INCLUDED
#define MYIO_H_INCLUDED

#include<cstring>
#include<iostream>
#include <vector>


template<typename T>
void print(T& input)
{
    std::cout<<input<<std::endl;
    return;
}
template<typename T>
void print(T&& input)
{
    std::cout<<input<<std::endl;
    return;
}
#ifdef vecnewline
template<typename T>
void print(std::vector<T> &arr, char delimeter='\n')
{
    if(arr.size()==0)return;
    auto it=arr.begin();
    std::cout<<*it; it++;
    for(; it!=arr.end();it++)
    {
        std::cout<<delimeter<<*it;
    }
    std::cout<<std::endl;
    return;
}
#else
template<typename T>
void print(std::vector<T> &arr, char delimeter=' ')
{
    if(arr.size()==0)return;
    auto it=arr.begin();
    std::cout<<*it; it++;
    for(; it!=arr.end();it++)
    {
        std::cout<<delimeter<<*it;
    }
    std::cout<<std::endl;
    return;
}
#endif
template<typename T>
void print(std::vector<T> &&arr)
{
    print(arr);
}
template<typename T>
void print(const std::vector<T> &arr, char delimeter=' ')
{
    if(arr.size()==0)return;
    auto it=arr.begin();
    std::cout<<*it; it++;
    for(; it!=arr.end();it++)
    {
        std::cout<<delimeter<<*it;
    }
    std::cout<<std::endl;
    return;
}

template<typename T, typename... Args>
void print(T t, Args... args) // recursive variadic function
{
    print(t);

    print(args...) ;
}

template<typename T>
void input(T& v)
{
    std::cin>>v;
    return;
}

template<typename T>
void input(std::vector<T> &arr)
{
    for(auto&& x: arr)
    {
        std::cin>>x;
    }
    return;
}

template<typename T, typename... Args>
void input(T& t, Args&... args) // recursive variadic function
{
    input(t);

    input(args...) ;
}

#ifdef posix
#define pc(x) putchar_unlocked(x)
#define gc(x) getchar_unlocked(x)
#define fgc(x) fgetc_unlocked(x)
#define fpc(x,y) fputc_unlocked(x,y)
#else
#define pc(x) putchar(x)
#define gc(x) getchar(x)
#define fgc(x) fgetc(x)
#define fpc(x,y) fputc(x,y)
#endif // posix





#ifdef fastio
inline void print(unsigned long long num){
    if(num==0)
    {
        pc('0');
        pc('\n');
        #ifdef debug
        print("(fastio)");
		#ifdef posix
		print("using posix");
		#endif
        #endif
        return;
    }
    char s[32];
    register unsigned char i=0;
    while(num){
        s[i++]=(num%10)+'0';
        num/=10;
    }
    while(i--){
        pc(s[i]);
    }
    pc('\n');
    #ifdef debug
    print("(fastio)");
	#ifdef posix
	print("using posix");
	#endif
    #endif
}
inline void print(int num){
    if(num==0)
    {
        pc('0');
        pc('\n');
        #ifdef debug
        print("(fastio)");
		#ifdef posix
		print("(using posix)");
		#endif
        #endif
        return;
    }
    char s[16];
    register unsigned char i=0;
    while(num){
        s[i++]=(num%10)+'0';
        num/=10;
    }
    while(i--){
        pc(s[i]);
    }
    pc('\n');
    #ifdef debug
    print("(fastio)");
	#ifdef posix
	print("(using posix)");
	#endif
    #endif
}

inline void input(int &number)
{
    register char c;
    number = 0;
    c = gc();
    while(c<48||c>57){
        c=gc();
    }
    for (; (c>47 && c<58); c=gc())
        number = (number<<1)+(number<<3) + c - 48;
}
inline void input(unsigned long long &number)
{
    register char c;
    number = 0;
    c = gc();
    while(c<48||c>57){
        c=gc();
    }
    for (; (c>47 && c<58); c=gc())
        number = (number<<1)+(number<<3) + static_cast<unsigned long long>(c) - 48;
}
inline void input(char* str)
{
    //int sz=sizeof(str);
    register char c;
    register unsigned char i=0;
    c = gc();
    while(c<33||c>126){
        c=gc();
    }
    for (; (c!='\n'&&c!=' '&&c!='\t'); c=gc())
        str[i++] = c;
    str[i]='\0';
}
inline void input(float& number)
{
    number=0;
    register char c;
    register int nc=0;
    c = gc();
    while(c<48||c>57){
        c=gc();
    }
    for (; (c>47 && c<58); c=gc())
        nc = (nc<<1)+(nc<<3) + c - 48;
    number+=nc;
    if(c!='.')return;
    nc=0;
    c=gc();
    register float div=1;
    for (; (c>47 && c<58); c=gc())
        nc = (nc<<1)+(nc<<3) + c - 48,div*=10;
    number+=(nc/div);
}
#endif




#endif // MYIO_H_INCLUDED
