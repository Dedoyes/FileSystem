#ifndef __STORAGE_HPP
#define __STORAGE_HPP

void storageSuperBlock (void);
void readSuperBlock (void);

void storageFCB (void);
void readFCB (void);

void storageInodeForest (void); 
void readInodeForest (void);

void storageDiskIndexNodeCluster (void);
void readDiskIndexNodeCLuster (void);

void storageFileTree (void); 
void readFileTree (void);


#endif
