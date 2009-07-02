using System;
using System.Collections.Generic;
using System.Text;

using System.Runtime.InteropServices;

namespace CsTest
{
    public class Class1
    {
        [DllImport("cppdll.dll", EntryPoint = "?print@@YAXXZ")]
        public static extern void print1();

        [DllImport("cppdll.dll", EntryPoint = "?passIntByPointer@@YAXPAH@Z")]
        public static extern void passIntByPointer(out int i);

        [DllImport("cppdll.dll", EntryPoint = "?passIntByReference@@YAXAAH@Z")]
        public static extern void passIntByReference(ref int i);

        [DllImport("cppdll.dll", EntryPoint = "?passStringByCharPointer@@YAXPAD@Z")]
        public static extern void passStringByCharPointer(string s);

        [DllImport("cppdll.dll", EntryPoint = "?printInNamespace@smw@@YAXXZ")]
        public static extern void printInNamespace();

        static void method(int i)
        {
            i = 1;
        }

        static void method(out int i)
        {
            i = 2;
        }
        

        public static void Main(string[] args)
        {
            Console.WriteLine("Hello");
            print1();

            int i;
            method(out i);
            //int i = 1;
            //passIntByReference(ref i);
            //Console.WriteLine(i);

            //string s = "abcde";
            //passStringByCharPointer(s);

            printInNamespace();
        }
    }
}
