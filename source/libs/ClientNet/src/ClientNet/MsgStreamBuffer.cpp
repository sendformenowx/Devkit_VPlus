#include "MsgStreamBuffer.h"
#include "../../../ClientLib/src/NetProcessIn.h"

GlobalVar<CMemPool<(_TAG('MSG', 1)), CMsgStreamBuffer::SMsgStreamNode, 20, 1>, 0x00EECD98> CMsgStreamBuffer::SMsgStreamNode::m_mempool;

// IsOpcodeSupported_MAYBE .text 00841780 000000B4 00000008 00000008 R . . . . T .
bool IsOpcodeSupported(WORD msgid, int a2) {
    return reinterpret_cast<bool (__cdecl *)(WORD, int)>(0x00841780)(msgid, a2);
}

CMsgStreamBuffer::CMsgStreamBuffer(WORD msgid) {
    field_0xc = 0;
    m_msgid = msgid;

    SMsgStreamNode *node = new SMsgStreamNode;

    m_node1 = node;
    m_node2 = node;
    m_availableBytesForReading = 0;
    m_currentReadBytes = 0;
}

void *CMsgStreamBuffer::SMsgStreamNode::operator new(std::size_t sz) {
    return m_mempool->alloc();
}

CMsgStreamBuffer::SMsgStreamNode::SMsgStreamNode() {
    data[0] = 0;
    currentPos = &data[1];
}

// CMsgStreamBuffer::Write(char *,int) .text 00508FE0 000000B1 00000008 00000008 R . . . . T .
void CMsgStreamBuffer::Write(const void *data, size_t size) {
    reinterpret_cast<void (__thiscall *)(CMsgStreamBuffer *, const void *, size_t)>(0x00508FE0)(this, data, size);
}

CMsgStreamBuffer &CMsgStreamBuffer::operator<<(const std::n_string &str) {
    (*this) << (WORD) str.length();
    Write(str.c_str(), str.length());

    return *this;
}

CMsgStreamBuffer &CMsgStreamBuffer::operator<<(const std::string &str) {
    (*this) << (WORD) str.length();
    Write(str.c_str(), str.length());

    return *this;
}

CMsgStreamBuffer &CMsgStreamBuffer::operator<<(const std::n_wstring &str) {
    (*this) << (WORD) str.length();
    Write(str.c_str(), str.length() * 2);
    return *this;
}


void CMsgStreamBuffer::ToggleBefore() {
    if (field_0xc != 1) {
        field_0xc = 1;
        m_node2 = m_node1;
        m_availableBytesForReading = 0;
    }
}

void CMsgStreamBuffer::ToggleAfter() {
    if (field_0xc != 0) {
        field_0xc = 0;
        m_node2 = m_node1;
        m_currentReadBytes = 0;
    }
}

CMsgStreamBuffer::~CMsgStreamBuffer() {
    // TODO: This is a really, really, REALLY BAD idea. Implement this function ASAP!
    reinterpret_cast<void (__thiscall *)(CMsgStreamBuffer *)>(0x005097A0)(this);
}

WORD CMsgStreamBuffer::msgid() const {
    return m_msgid;
}

CMsgStreamBuffer &CMsgStreamBuffer::operator>>(std::n_string &str) {
    return reinterpret_cast<CMsgStreamBuffer &(__thiscall *)(CMsgStreamBuffer *, std::n_string &)>(0x004f7a70)(this, str);
}

void CMsgStreamBuffer::Read(void *value, size_t numBytes) {
    reinterpret_cast<void (__thiscall *)(CMsgStreamBuffer *, void *, size_t)>(0x004F7220)(this, value, numBytes);
}


std::string CMsgStreamBuffer::ReadStringA()
{
    unsigned short len; // i need read client packets like pandoralib you need wstring not string dude my PSMission is cant read 704C
    Read(len);

    int bufLen = len + 1;
    char* buffer = new char[bufLen]();

    Read((buffer), len);

    std::string result(buffer);

    delete[] buffer;

    return result;
}

CMsgStreamBuffer &CMsgStreamBuffer::operator>>(std::string &str) {
    return reinterpret_cast<CMsgStreamBuffer &(__thiscall *)(CMsgStreamBuffer *, std::string &)>(0x004f7a70)(this, str);
}

void CMsgStreamBuffer::FlushRemaining() {
    m_currentReadBytes = m_availableBytesForReading;
}


CMsgStreamBuffer &CMsgStreamBuffer::operator>>(std::n_wstring &str) {
    return reinterpret_cast<CMsgStreamBuffer &(__thiscall *)(CMsgStreamBuffer *, std::n_wstring &)>(0x005b5e50)(this, str);
}

void CMsgStreamBuffer::SendToClient()
{
    class CDummyScene;
#define g_CurrentScene (*((CDummyScene**)0x00EECEA4))
    //CNetProcessIn::ProcessItemMovementResult(g_CurrentScene, this);
}

unsigned __int32 CMsgStreamBuffer::GetLength() const { return m_currentReadBytes; }

void CMsgStreamBuffer::Seek(unsigned __int32 offset)
{
    assert((offset <= GetLength()) && "cannot seek beyound msg data bounds");
    m_currentReadBytes = offset;
}