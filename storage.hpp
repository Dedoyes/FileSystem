#ifndef __STORAGE_HPP
#define __STORAGE_HPP

void storageSuperBlock (void);
void readSuperBlock (void);

void storageInodeForest (void); 
void readInodeForest (void);

void storageDiskIndexNodeCluster (void);
void readDiskIndexNodeCLuster (void);

void storageFileTree (void); 
void readFileTree (void);

void storageUserGroup (void);
void readUserGroup (void);

void load (void);

void storage (void);

#endif
