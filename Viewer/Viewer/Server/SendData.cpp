#include "SendData.h"
#include "MoodConnection.h"

void Init_Buffer_Socket_input(std::vector<char>& buf, Input_Kboard_Mouse s_mi)
{
	s_mi.kInput.Init(buf, 1);
	s_mi.mInput.Init(buf, 2);

	Sleep(90);

}
void Init_Buffer_Socket_resol_C(std::vector<char>& buf)
{
	EntryData::Monitoring mData;

	buf[0] = ((char)mData.resol_C);
}
void Send_Data_Packet(SOCKET sData)
{
	int res = 0;
	std::vector<char>buf(COUNT_BUFFER_CELLS);

	Input_Kboard_Mouse _input;
	Cursor_info Cinfo;
	EntryData::Monitoring mData;

	_input.kInput.createdi();
	_input.mInput.createdi();


	while (res != -1)                                        // todo set condition
	{
		Init_Buffer_Socket_resol_C(buf);
		Init_Buffer_Socket_input(buf, _input);
		Init_Buffer_Socket_CurPose(buf, 3, 4, 5, 6, Cinfo, mData.hWindowPaint);

		res = send(sData, buf.data(), COUNT_BUFFER_CELLS, 0);

		buf[1] = (char)0;
		buf[2] = (char)0;


		Sleep(1);
	}
	_input.kInput.destroydi();
	_input.mInput.destroydi();

	MoodConnection::OpenConnection = 0;
}