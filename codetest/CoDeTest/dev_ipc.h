
#ifndef __MP_IPC_HEADER__
#define __MP_IPC_HEADER__

#ifdef __cplusplus
extern "C"
{
#endif

gboolean DevIPCStart(DevMsgHandle hMsg, int ipcKey);
void DevIPCDestroy();
void MPIPC_GstEvtCB(int event, void *data, int data_size);
void DevIPC_SendtoUI(int event, void *data, int data_size);

#ifdef __cplusplus
}
#endif

#endif
