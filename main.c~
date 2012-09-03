
#include<string.h>

#define u8 unsigned char 
#define u16 unsigned short 
#define u32 unsigned long

typedef struct ext2_inode {
	u16	i_mode;		/* File mode */
	u16	i_uid;		/* Owner Uid */
	u32	i_size;		/* Size in bytes */
	u32	i_atime;	/* Access time */
	u32	i_ctime;	/* Creation time */
	u32	i_mtime;	/* Modification time */
	u32	i_dtime;	/* Deletion Time */
	u16	i_gid;		/* Group Id */
	u16	i_links_count;	/* Links count */
	u32	i_blocks;	/* Blocks count */
	u32	i_flags;	/* File flags */
        u32     dummy;
	u32	i_block[15];    /* Pointers to blocks */
        u32     pad[7];         /* inode size MUST be 128 bytes */
} INODE;

typedef struct ext2_group_desc
{
	u32	bg_block_bitmap;		/* Blocks bitmap block */
	u32	bg_inode_bitmap;		/* Inodes bitmap block */
	u32	bg_inode_table;		/* Inodes table block */
	u16	bg_free_blocks_count;	/* Free blocks count */
	u16	bg_free_inodes_count;	/* Free inodes count */
	u16	bg_used_dirs_count;	/* Directories count */
	u16	bg_pad;
	u32	bg_reserved[3];
} GD;

typedef struct ext2_dir_entry_2 {
	u32	inode;			/* Inode number */
	u16	rec_len;		/* Directory entry length */
	u8	name_len;		/* Name length */
	u8	file_type;
	char	name[255];      	/* File name */
} DIR;

char* cp; 
INODE* ip;
DIR *dp;

char* table = "0123456789"; 

// Recursive driver for printing integers
//void rprinti(x) int x; 
//{ 
	//char c; 
	//if(x)
	//{
		//c = table[x % 10]; 
		//rprinti(x/10); 
		//putc(c); 
	//}
//}

// Main function for printing integers 
//void printi(x) int x; 
//{
	//if(x==0) 
	//{ 
		//putc('0'); 
		//return; 
 	//}
	//rprinti(x); 
//}

// Print string
void prints(s) char* s; 
{
	 
	while(*s != NULL)
	{
		putc(*s);  
		s++; 
	}
}

void get_block(blk, buff) int blk; char buff[]; 
{
	
	diskr(blk/18, (blk/9)%2, (blk*2)%18, buff);
}

unsigned long get_ino(name, buff) char* name; char buff[]; 
{
	int inodeNumber; 
	char nameBuff[256];
	

	inodeNumber = 0; 

	cp = buff; 
	dp = (DIR *)cp; 

	while(cp < &buff[1024])
	{ 
		//strncpy(nameBuff, dp->name, dp->name_len); 
		//nameBuff[dp->name_len] = 0; 		// Add null terminator 
		//prints("\n\r"); prints(dp->name); 
		//prints(" "); printi(dp->inode); 

		if(!strncmp(dp->name, name, dp->name_len))
		{
			//prints("\n\rFound "); prints(name);
			//prints("...returning inodeNumber "); 
			//printi(dp->inode);  
			return dp->inode; 
		}

		cp += dp->rec_len; 			// Go to next directory 
		dp = (DIR *)cp;
	}
	//prints("\n\rCould not find "); prints(name); 
	return inodeNumber; 	// Returns 0 
	
}


void gets(s) char* s; 
{
	 
	*s = getc(); 
	while(*s != '\r')	// while the Enter key is not pressed 
	{
		
		putc(*s); 	// echo the character 
		s++; 		// move to the next spot in the char array 
		*s = getc();  	// read another character 
	}
	
}

void ShowPrompt() void; 
{
	//prints("Enter boot image (Press Enter for default MTX): ");  
	prints("?"); 
}

int main()
{
	 
	char s[24]; 	// the name of the desired boot_file. I.e., mtx for /boot/mtx
	int inodeNumber; 
	int nextBlock; 
	int useDefault = 0; 	// Default: search for 'mtx' in /boot/
	char buff[1024]; 
	char buff2[1024]; 
	//char buff3[1024]; 
	u32* up; 
	int i; 

	inodeNumber = 0; 
	while(inodeNumber == 0)
	{
		ShowPrompt(); 
		gets(s);		// Read user input of desired boot image

		if(*s == '\r')
		{ 
			useDefault = 1; 
		} 

		get_block(5, buff); 	// Load block 5 which is where Inodes table begins
	  
		
		ip = (INODE *)buff + 1; 	// Read in root INODE
		//ip++; 			// ip points to root INODE which is inode#2, we don't need 							SuperBlock, GroupDescriptor, etc.
		 

		get_block((int)ip->i_block[0], buff);	// Read root->i_block[0] into buff 
		// I've looked through and discovered that all of the i_blocks in root 
			// are empty except i_block[0]

		inodeNumber = get_ino("boot", buff); 	// Get inode # of boot directory 
							// inodeNumber = 13 
		if(inodeNumber == 0)
		{
			//prints("\n\rFailed to find boot directory."); 
			return; 	
		} 

		// Do some error checking, make sure the inodeNumber != 0 
		// We have the inodeNumber of the boot directory, use Mailman's algorithm to get block 
		nextBlock = ((inodeNumber - 1)/8) + 5; 	// Calculate the block # where boot's data is stored 
					// 

		//prints("\n\rboot block = "); 
		//printi(nextBlock); 

		get_block(nextBlock, buff); 	// Read boot's data block into buff 
		ip = (INODE *)buff; 
		ip += (inodeNumber-1)%8; 
		get_block((int)ip->i_block[0], buff); 

		 
		if(useDefault)
		{
			//prints("Searching for MTX..."); 
			s[0] = 'm'; 
			s[1] = 't'; 
			s[2] = 'x'; 	
			s[3] = 0; 	// most space efficient way to assign array :) 

			inodeNumber = get_ino(s, buff); 
		}
		else
		{
			//prints("Searching for "); prints(s); prints("..."); 
			inodeNumber = get_ino(s, buff);
		}
	
		 
	}

	// Now we have the inodeNumber of the boot image (mtx)
	 
	nextBlock = ((inodeNumber - 1)/8) + 5; 	// Calculate the block # where mtx' data is stored 

	
	get_block(nextBlock, buff); // Read mtx' data block into buff
	ip = (INODE *)buff; 
	ip += (inodeNumber-1)%8;	// ip now points to inode of mtx 

	 
	get_block((int)ip->i_block[12],buff2);      // Load indirect blocks into buff2
	
	//get_block((int)ip->i_block[13],buff3);  // Load the first double indirect block into buff3     
	 
	//up = (int*)buff3; 

	//get_block((int)*up, buff3); 

	// Since ES points to 0x1000, get_block at 0 offset will put this all in memory 
	setes(0x1000);		// Set ES to 0x1000
	for(i = 0; i<12; i++)
    	{ 
		get_block((int)ip->i_block[i],0);
      		inces();   
   	}
	//putc('1'); 
	
	up = buff2; 
	
	for(i=0; i<256; i++)
	{
		get_block(*up, 0); 
		inces(); 	
		up++; 
	}

	return 1; 
	// inces() - increment ES by 0x40 (1KB)

	// Repeat until MTX has been completely loaded into memory 
	// (3) Find the disk blocks of the file
		// i_block[0] to i_block[11] are DIRECT 
		// i_block[12] are INDIRECT blocks 
	// (4) Load the disk blocks into memory at segment 0x1000 
	// (5) return 1 to bs.s for OK, return 0 for failure

	
	//prints("\n\rBooting "); 
	//prints(s); 




}
