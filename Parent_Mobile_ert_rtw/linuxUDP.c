/**
 * @file linuxUDP.c
 * Copyright 2009-2017 The MathWorks, Inc.
 */

#include <assert.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <fcntl.h>
#include "rtwtypes.h"

/* BEGIN INLINE OF #include "DAHostLib_Network.h" */

/* Wrap everything in extern C */
#ifdef __cplusplus
extern "C" {
#endif 

extern const char *libName_Network;

typedef enum {
    NETWORK_INPUT  = 0,
    NETWORK_OUTPUT = 1
} NetworkInputOrOutput;

/*******************************
 * Routines which are defined in the library in question
 *******************************/
typedef void (*pFnLibCreate_Network)(void **device, char *err, NetworkInputOrOutput inOut, const char *localURL, int localPort, 
                             const char *remoteURL, int remotePort, int bufferSize, int bytesPerSample, int blockingTime);
typedef void (*pFnLibUpdate_Network)(void *device, char *err, const void *src, int nSamples);
typedef void (*pFnLibOutputs_Network)(void *device, char *err, void *src, int* nSamples);

/*******************************
 * Routines which we define to call the functions in the library 
 *******************************/

void CreateUDPInterface(void *hl);
void DestroyUDPInterface(void *hl);

void LibCreate_Network(void *hostLib, int inOut, const char *localURL, int localPort, 
                       const char *remoteURL, int remotePort, int bufferSize, int bytesPerSample, int blockingTime);
void LibUpdate_Network(void *hostLib, const void *src, int nSamples);
void LibOutputs_Network(void *hostLib, void *src, int *nSamples);

/* Include HostLib for declarations of LibStart, LibTerminate, CreateHostLibrary, and DestroyHostLibrary. */
#include "DAHostLib_rtw.h"

#ifdef __cplusplus
} // extern "C"
#endif 

/* END INLINE OF #include "DAHostLib_Network.h" */


typedef struct tgtsockstruct {
    int sockfd;
    struct sockaddr_in localsockaddr;
    struct sockaddr_in remotesockaddr;
    int dataTypeSize;
} TgtSockStructT;


void TGT_libCreate(void **device_, char *err, NetworkInputOrOutput io, 
       const char *localURL, int localPort, const char *remoteURL, 
       int remotePort, int bufferSize, int dataTypeSize, int blockingTime);
void TGT_libUpdate(void *device, char *err, const void *src, int nSamples);
void TGT_libStart(void *device, char *err);
void TGT_libOutputs(void *device, char *err, void *src, int *nSamples);
void TGT_libTerminate(void *device, char *err);
void TGT_libDestroy(void *device, char *err, int type);


void CreateTargetUDPInterface(void *hl) 
{
    HostLibrary *hostLib = (HostLibrary*)hl;
    *hostLib->errorMessage = '\0';
    memset(hostLib, 0, sizeof(HostLibrary));

    /* Indicate that the structure is valid for future function calls. */    
    hostLib->library      = (void*) 1;
    
    /* Set the function pointers to point to target UDP implementation. */    
    hostLib->libCreate    = (void*) TGT_libCreate;
    hostLib->libStart     = (void*) TGT_libStart; 
    hostLib->libReset     = (void*) NULL; 
    hostLib->libUpdate    = (void*) TGT_libUpdate;
    hostLib->libOutputs   = (void*) TGT_libOutputs;
    hostLib->libTerminate = (void*) TGT_libTerminate;
    hostLib->libDestroy   = (void*) TGT_libDestroy;
}


void DestroyTargetUDPInterface(void *hl) 
{
    HostLibrary *hostLib = (HostLibrary*)hl;
    if(hostLib->library) {
        /* Clear the structure (except for any possible error message). */
		memset(hostLib, 0, sizeof(HostLibrary) - MAX_ERR_MSG_LEN);
    }
}


void TGT_libCreate(void **device_, char *err, NetworkInputOrOutput io, 
       const char *localURL, int localPort, const char *remoteURL, 
       int remotePort, int bufferSize, int dataTypeSize, int blockingTime)
{
    int flags;
    struct timeval tv;
    int ret;
    TgtSockStructT *device;
	/* verification of the local port*/
	/* case it lower than zero, assign to zero so it can dynamically assigned */
	if(localPort < 0)
	{
		localPort = 0;
	}
		
	
	
    device = (TgtSockStructT *) malloc (sizeof(TgtSockStructT)); 
    
    bzero(&device->remotesockaddr, sizeof(device->remotesockaddr));
    device->remotesockaddr.sin_family = AF_INET;
    device->remotesockaddr.sin_port = htons(remotePort);
    inet_aton(remoteURL, &device->remotesockaddr.sin_addr);
    
    bzero(&device->localsockaddr, sizeof(device->localsockaddr));
    device->localsockaddr.sin_family = AF_INET;
    device->localsockaddr.sin_port = htons(localPort);
    inet_aton(localURL, &device->localsockaddr.sin_addr); 
    
    device->sockfd = socket(AF_INET, SOCK_DGRAM, 0);    
    if ( device->sockfd < 0) {
        printf ("error creating socket\n");
    }
    if   ( (device->remotesockaddr.sin_addr.s_addr == INADDR_BROADCAST) ||
            (device->localsockaddr.sin_addr.s_addr == INADDR_BROADCAST) ) {
        static int broadcast_en = 1;
        ret = setsockopt(((TgtSockStructT *) device)->sockfd, SOL_SOCKET,
                SO_BROADCAST, &broadcast_en, sizeof(broadcast_en));
        if (ret < 0) {
            perror("ERROR in SO_BROADCAST");
        }
    }
	if ( io == NETWORK_INPUT )
	{
		ret = setsockopt(((TgtSockStructT *) device)->sockfd, SOL_SOCKET,
                SO_SNDBUF, &bufferSize, sizeof(bufferSize));
	}
	else if(io == NETWORK_OUTPUT)
	{
		ret = setsockopt(((TgtSockStructT *) device)->sockfd, SOL_SOCKET,
                SO_SNDBUF, &bufferSize, sizeof(bufferSize));
	}
	else
	{
		ret = -1;
		perror("INVALID NetworkIOValue");
	}
    if (ret < 0)
    {
        perror("ERROR in setsockopt");
    }else
	{
		
		int realSize = 0;
		int len = sizeof(realSize);
		

		
		if ( io == NETWORK_INPUT )
		{
			getsockopt(((TgtSockStructT *) device)->sockfd,SOL_SOCKET,SO_RCVBUF,&realSize, &len);
			
		}
		else
		{
			getsockopt(((TgtSockStructT *) device)->sockfd,SOL_SOCKET,SO_SNDBUF,&realSize, &len);
		}
		if (realSize < bufferSize)
		{
			fprintf(stderr, "Buffer requested size: %d Bytes. Socket buffer limit: %d Bytes\n",bufferSize,realSize);
			
		}
	}

    if(blockingTime == 0) { 
        /* set non-blocking socket option */
        flags = fcntl(((TgtSockStructT *) device)->sockfd, F_GETFL, 0);
        fcntl(((TgtSockStructT *) device)->sockfd, F_SETFL, flags | O_NONBLOCK);      
    }
    else if(blockingTime != MIN_int32_T) 
    { 
        /* if not set to inf in the block mask */
        tv.tv_sec  = (long) (blockingTime/1000);
        tv.tv_usec = (long) (blockingTime % 1000);    
        setsockopt(((TgtSockStructT *) device)->sockfd, SOL_SOCKET, 
                SO_RCVTIMEO, &tv, sizeof(tv));
    }       

    device->dataTypeSize = dataTypeSize;
    *device_ = device;

    err[0] = '\0';
}


void TGT_libStart(void *device, char *err) 
{
    if(device) {
        bind(((TgtSockStructT *) device)->sockfd, 
             (struct sockaddr *) &((TgtSockStructT *) device)->localsockaddr, 
             sizeof(((TgtSockStructT *) device)->localsockaddr));
    }
}


void TGT_libUpdate(void *device, char *err, const void *src, int nSamples)
{
    int n;  
    if(device) {   
        n = sendto(((TgtSockStructT *) device)->sockfd, src, 
                   ((TgtSockStructT *) device)->dataTypeSize * nSamples, 0, 
                   (struct sockaddr *) &((TgtSockStructT *) device)->remotesockaddr, 
                   sizeof(((TgtSockStructT *) device)->remotesockaddr));
        /* if(n<0)
            printf("error writing to socket\n");
        */
    }
}


void TGT_libOutputs(void *device, char *err, void *src, int *nSamples)
{
    int numBytesReceived = 0;
    int dTypeSize = ((TgtSockStructT *)device)->dataTypeSize;
    size_t nBytesToRead = dTypeSize * (*nSamples);
    if(device) {
        numBytesReceived = recvfrom(((TgtSockStructT *) device)->sockfd,
                src, nBytesToRead, 0, NULL, NULL);
        if (numBytesReceived > 0) {
            *nSamples = (int) (numBytesReceived / dTypeSize); /* Return number of bytes received */
        }
        else {
            *nSamples = 0; /* No UDP packets received */
        }
    }
}


void TGT_libTerminate(void *device, char *err)
{
    /* NOP; */
}


void TGT_libDestroy(void *device, char *err, int type) 
{
    if(device)
        free(device);
}
