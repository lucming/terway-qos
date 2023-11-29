// //section demo with gcc
// #include "stdio.h"  

// #if defined(__APPLE__) && defined(__MACH__)
//  #define FORCE_USED_SECTION __attribute__((used)) __attribute__((section ("__OPENOCD,__openocd")))
// #else
//  #define FORCE_USED_SECTION __attribute__((used)) __attribute__((section (".openocd")))
// #endif

// FORCE_USED_SECTION  
// int __attribute__((section("my_fun"))) test1(int a,int b)  
// {  
//  return (a+b);  
// }

// int test(int b)  
// {  
//  return 2*b;  
// }

// FORCE_USED_SECTION
// int __attribute__((section("my_fun"))) test0(int a,int b)  
// {  
//  return (a*b);  
// }  
// FORCE_USED_SECTION  
// int __attribute__((section("my_var"))) chengi;  
// int __attribute__((section("my_var"))) chengj;  
   
// int main(void)  
// {  
//  int sum,c,j;    
//  chengi=1,chengj=2;  
   
//  sum=test1(chengi,chengj);  
//  c=test(100);  
//  j=test0(chengi,chengj);  
       
//   printf("sum=%d,c=%d,j=%d\r\n",sum,c,j);  

//   return 0;  
// }  

// #include <stdio.h>

// extern int start_mysection __asm("section$start$__DATA$__mysection");
// extern int stop_mysection  __asm("section$end$__DATA$__mysection");

// // If you don't reference x, y and z explicitly, they'll be dead-stripped.
// // Prevent that with the "used" attribute.
// static int x __attribute__((used,section("__DATA,__mysection"))) = 4;
// static int y __attribute__((used,section("__DATA,__mysection"))) = 10;
// static int z __attribute__((used,section("__DATA,__mysection"))) = 22;

// int main(void)
// {
//     long sz = &stop_mysection - &start_mysection;
//     long i;

//     printf("Section size is %ld\n", sz);

//     for (i=0; i < sz; ++i) {
//         printf("%d\n", (&start_mysection)[i]);
//     }

//     return 0;
// }


//#include <string.h>
//#include <stdio.h>
//#include "tools.h"
//#include "mod.h"
//
//#define __FILENAME__    (strrchr(__FILE__, '\\') ? (strrchr(__FILE__, '\\') + 1) : __FILE__)
//
//int main(int argc, char **argv)
//{
//    printf("%s, %s, %d\n", __FILE__, __FILENAME__, __LINE__);
//    say1();
//    printf("%d\n",num);
//
//    return 0;
//}

#include <stdio.h>
#include <stdlib.h>
int main(int argc, char **argv){
    int count = 4;
    printf("111 count:%d\n",count);
    int retval = __sync_fetch_and_add(&count,10);

    printf("222 retval:%d\n",retval);
    printf("222 count:%d\n",count);

    return 0;
}


//#include <linux/bpf.h>
//#include <linux/pkt_cls.h>
//#include <stdint.h>
//#include <iproute2/bpf_elf.h>
//
//#define __x86_64__ 1
//#define __LP64__ 1
//
//#ifndef __section
//# define __section(NAME)                  \
//   __attribute__((section(NAME), used))
//#endif
//
//#ifndef __inline
//# define __inline                         \
//   inline __attribute__((always_inline))
//#endif
//
//// 共享的Map是全局变量，因此访问它的时候需要同步
//#ifndef lock_xadd
//# define lock_xadd(ptr, val)              \
//   ((void)__sync_fetch_and_add(ptr, val))
//#endif
//
//// 这个宏用于将BPF助手函数映射到C代码
//// 函数map_lookup_elem被映射到定义uapi/linux/bpf.h在中的枚举值 BPF_FUNC_map_lookup_elem
//// 在载入内核后，Verifier会检查传入的参数是否为期望的类型，并且将对助手函数的调用指向真实函数的调用
//#ifndef BPF_FUNC
//# define BPF_FUNC(NAME, ...)              \
//   (*NAME)(__VA_ARGS__) = (void *)BPF_FUNC_##NAME
//#endif
//
//static void *BPF_FUNC(map_lookup_elem, void *map, const void *key);
//// static void (*map_lookup_elem)(void *map, const void *key) = (void *)BPF_FUNC_map_lookup_elem;
//
//
//
//
//// 这个是共享的Map，类型struct bpf_elf_map是iproute2定义的
//// iproute2提供了公共的BPF ELF loader，因此struct bpf_elf_map对于XDP和tc程序来说是一样的
////                         必须放在maps段，这样loader才能发现
////                         可以定义多个Map，都必须放在maps段
//struct bpf_elf_map acc_map __section("maps") = {
//    .type           = BPF_MAP_TYPE_ARRAY,
//    .size_key       = sizeof(uint32_t),
//    .size_value     = sizeof(uint32_t),
//    // 该Map被Pin到PIN_GLOBAL_NS，这意味着Map将被tc钉为BPF伪文件系统中的位于
//    // /sys/fs/bpf/tc/globals/目录下的节点。对于此acc_map，节点路径为
//    // /sys/fs/bpf/tc/globals/acc_map
//    // global是跨越多个Object文件的全局命名空间。如果不同BPF程序中均有名为acc_map
//    // 的Map映射到PIN_GLOBAL_NS，这这些程序会共享统一Map。仅仅第一个载入的BPF程序会触发
//    // Map的创建，后续载入的程序直接使用
//
//    // 如果取值PIN_NONE则不会映射为BPF文件系统中的节点，当tc退出后，无法从用户空间访问Map
//    .pinning        = PIN_GLOBAL_NS,
//    .max_elem       = 2,
//};
//
//// 这个是共享的内联函数
//static __inline int account_data(struct __sk_buff *skb, uint32_t dir)
//{
//    uint32_t *bytes;
//    // 将Map传递给助手函数
//    bytes = map_lookup_elem(&acc_map, &dir);
//    if (bytes)
//            lock_xadd(bytes, skb->len);
//
//    return TC_ACT_OK;
//}
//
//// 两个段，都会调用account_data往Map中写入数据
//__section("ingress")
//int tc_ingress(struct __sk_buff *skb)
//{
//    return account_data(skb, 0);
//}
//
//__section("egress")
//int tc_egress(struct __sk_buff *skb)
//{
//    return account_data(skb, 1);
//}
//
//char __license[] __section("license") = "GPL";