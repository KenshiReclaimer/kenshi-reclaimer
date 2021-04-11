using System;
using Reclaimer.Core;
using Reclaimer.Shinobi;

namespace Reclaimer.CoreTesting
{

    [NativeFunction]
    [ByteSignature("11 22 33 44 55")]
    public delegate void DoTheThingHehe();

    [NativeGlobal]
    [ByteSignature("AA ?? BB ?? CC")]
    public class GameWorld
    {

    }

    class Program
    {
        static void Main(string[] args)
        {
            var m = new MemoryManager();
            m.scan.CollectScans();
        }
    }
}
