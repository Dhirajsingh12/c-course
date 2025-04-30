#include <stdio.h>
#include <stdlib.h>

#define MAX_SIZE 100
#define FREE -1

int disk[MAX_SIZE];
int disk_size = MAX_SIZE;

// Function to initialize the disk
void initializeDisk()
{
    for (int i = 0; i < disk_size; i++)
    {
        disk[i] = FREE;
    }
}

// Allocate contiguous blocks and store a single data value
int allocateContiguous(int start_block, int num_blocks, int data)
{
    if (start_block < 0 || start_block + num_blocks > disk_size)
    {
        return -1;
    }

    // Check if all blocks in the range are free
    for (int i = start_block; i < start_block + num_blocks; i++)
    {
        if (disk[i] != FREE)
        {
            return -1; // Space is not free
        }
    }

    // Allocate all blocks with the same data
    for (int i = start_block; i < start_block + num_blocks; i++)
    {
        disk[i] = data;
    }

    return start_block;
}

// Free allocated blocks by resetting to -1
void freeContiguous(int start_block, int num_blocks)
{
    if (start_block < 0 || start_block + num_blocks > disk_size)
    {
        printf("Invalid range to free.\n");
        return;
    }

    for (int i = start_block; i < start_block + num_blocks; i++)
    {
        disk[i] = FREE;
    }

    printf("Blocks from %d to %d freed.\n", start_block, start_block + num_blocks - 1);
}

// Display disk status
void displayDisk()
{
    printf("Disk Status (FREE = -1):\n");
    for (int i = 0; i < disk_size; i++)
    {
        printf("%d ", disk[i]);
    }
    printf("\n");
}

// Show occupied blocks and their data
void showOccupiedBlocks()
{
    printf("Occupied Blocks:\n");
    int found = 0;
    for (int i = 0; i < disk_size; i++)
    {
        if (disk[i] != FREE)
        {
            printf("Block %d -> Data: %d\n", i, disk[i]);
            found = 1;
        }
    }
    if (!found)
    {
        printf("No blocks are currently occupied.\n");
    }
}

// Count the number of files (contiguous blocks) in the disk
int countFiles()
{
    int fileCount = 0;
    int inFile = 0;
    int fileStart = -1;

    for (int i = 0; i < disk_size; i++)
    {
        if (disk[i] != FREE && !inFile)
        {
            fileStart = i;  // Mark the start of a file
            inFile = 1;     // We're inside a file now
        }
        else if (disk[i] == FREE && inFile)
        {
            printf("File %d: Start = %d, End = %d\n", ++fileCount, fileStart, i - 1);
            inFile = 0;   // We've left a file
        }
    }

    // If the last file reaches the end of the disk
    if (inFile)
    {
        printf("File %d: Start = %d, End = %d\n", ++fileCount, fileStart, disk_size - 1);
    }

    return fileCount;
}

// Display free space ranges (contiguous free blocks)
void displayFreeSpaceRanges()
{
    int inFreeSpace = 0;
    int freeStart = -1;

    printf("Free Space Ranges:\n");
    for (int i = 0; i < disk_size; i++)
    {
        if (disk[i] == FREE && !inFreeSpace)
        {
            freeStart = i;  // Start of a free space range
            inFreeSpace = 1;
        }
        else if (disk[i] != FREE && inFreeSpace)
        {
            printf("Free range: Start = %d, End = %d\n", freeStart, i - 1);
            inFreeSpace = 0;
        }
    }

    // If the free space reaches the end of the disk
    if (inFreeSpace)
    {
        printf("Free range: Start = %d, End = %d\n", freeStart, disk_size - 1);
    }
}

// Display free space
void displayFreeSpace()
{
    int freeSpace = 0;
    for (int i = 0; i < disk_size; i++)
    {
        if (disk[i] == FREE)
        {
            freeSpace++;
        }
    }
    printf("Total Free space: %d blocks\n", freeSpace);
}

int main()
{
    int choice;
    int start_block, num_blocks, data;

    initializeDisk();

    do
    {
        printf("\n----- Disk Allocation Menu -----\n");
        printf("1. Allocate Contiguous Blocks with One Data Value\n");
        printf("2. Free Contiguous Blocks\n");
        printf("3. Display Disk Status\n");
        printf("4. Count Files and Display Free Space\n");
        printf("5. Show Occupied Blocks\n");
        printf("6. Show Free Space Ranges\n");
        printf("7. Exit\n");
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice)
        {
        case 1:
            printf("Enter starting block index: ");
            scanf("%d", &start_block);
            printf("Enter number of blocks to allocate: ");
            scanf("%d", &num_blocks);
            printf("Enter data to store in all allocated blocks: ");
            scanf("%d", &data);

            if (allocateContiguous(start_block, num_blocks, data) != -1)
            {
                printf("Blocks allocated from %d to %d with data %d.\n", start_block, start_block + num_blocks - 1, data);
            }
            else
            {
                printf("Allocation failed. Not enough space or invalid input.\n");
            }

            displayFreeSpaceRanges();  // Show free space ranges after allocation
            break;

        case 2:
            printf("Enter starting block index to free: ");
            scanf("%d", &start_block);
            printf("Enter number of blocks to free: ");
            scanf("%d", &num_blocks);
            freeContiguous(start_block, num_blocks);

            displayFreeSpaceRanges();  // Show free space ranges after freeing blocks
            break;

        case 3:
            displayDisk();
            break;

        case 4:
            printf("Number of files (contiguous allocated blocks): %d\n", countFiles());
            displayFreeSpace();  // Display free space after every operation
            break;

        case 5:
            showOccupiedBlocks();
            break;

        case 6:
            displayFreeSpaceRanges();  // Show free space ranges
            break;

        case 7:
            printf("Exiting program.\n");
            break;

        default:
            printf("Invalid choice. Please try again.\n");
        }

    } while (choice != 7);

    return 0;
}