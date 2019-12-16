// Old version
Address processToPhysical(pid, Vaddr)
{
   PageInfo pages[] = getPageInfo(pid);
   uint pageno = Vaddr / PageSize;
   uint offset = Vaddr % PageSize;
   return pages[pageno].mem + offset;
}

PPPPPPPPPPPPPPQQQQQQQQQQQQ    2^12  n=12
00000000000000111111111111
11111111111111000000000000

// New version

Address processToPhysical(pid, Vaddr)
{
   PageInfo pages[] = getPageInfo(pid);
   uint mask   = (1 << 12) - 1;  // lower n bits set
   uint offset = Vaddr & mask;
   uint pageno = Vaddr >> 12;
   uint frame  = pages[pageno].frameNo;
   uint Paddr  = (frame << 12) | offset;
   return Paddr;
}
