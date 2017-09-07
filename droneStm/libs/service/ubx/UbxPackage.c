#include "UbxPackage.h"
#include <stdlib.h>
#include <string.h>

UbxChecksum calUbxChecksum(UbxHeader header,u8 *content){
	u8 *buffer;
	u8 ckA=0,ckB=0;
	UbxChecksum res;
	buffer=malloc(header.length+4);
	memcpy(buffer,&header._class,1);
	memcpy(buffer+1,&header.id,1);
	memcpy(buffer+2,&header.length,2);
	memcpy(buffer+4,content,header.length);
	for(int i=0;i<header.length+4;i++){
		ckA+=buffer[i];
		ckB+=ckA;
	}
	res.ckA=ckA;
	res.ckB=ckB;
	free(buffer);	
	return res;
}

void resetUbxHeader(UbxHeader *specPackage){
	 specPackage->id=specPackage->length=specPackage->_class=0;
}



void initUbxHeader(UbxHeader *header,u8 _class,u8 id,u16 length){
	header->_class=_class;
	header->id=id;
	header->length=length;
}

void createUbxPackage(UbxPackage *package,UbxHeader header,u8 *content){
	reCreateUbxPackage(package,header);
	memcpy(package->content,content,header.length);
	package->checksum=calUbxChecksum(header,content);
}

void createUbxPackageWithoutContent(UbxPackage *package,UbxHeader header){
	reCreateUbxPackage(package,header);
}


void copyUbxPackage(UbxPackage *des,UbxPackage source){
	reCreateUbxPackage(des,source.header);
	memcpy(des->content,source.content,source.header.length);
	des->checksum=source.checksum;
}

void reCreateUbxPackage(UbxPackage *package,UbxHeader header){
	if(!isUbxPackageNull(package))
		deleteUbxPackage(package);
	package->content=(u8*)malloc(header.length);
	package->header=header;
}


void deleteUbxPackage(UbxPackage *package){
	if(!isUbxPackageNull(package))
		return ;
	free(package->content);
	package->content=NULL;
}




int isUbxPackageNull(UbxPackage *package){
	return package->content==NULL;
}





int equalsUbxPackage(UbxPackage package1,UbxPackage package2){
	return	equalUbxHeader(package1.header,package2.header);
}

int equalUbxHeader(UbxHeader spec1,UbxHeader spec2){
	return spec1.id==spec2.id&&spec1._class==spec2._class;
}

int equalUbxChecksum(UbxChecksum cs1,UbxChecksum cs2){
	return cs1.ckA==cs2.ckA&&cs1.ckB==cs2.ckB;
}



void ubxPackageToBytes(UbxPackage package,u8 *out){
	out[0]=SYMBOL_1;
	out[1]=SYMBOL_2;
	out[2]=package.header._class;
	out[3]=package.header.id;
	out[4]=(u8)package.header.length;
	out[5]=(u8)(package.header.length>>8);
	memcpy(out+6,package.content,package.header.length);
	out[package.header.length+6]=package.checksum.ckA;
	out[package.header.length+7]=package.checksum.ckB;
}

int getSizeUbxPackage(UbxPackage package){
	return package.header.length+8;
}
