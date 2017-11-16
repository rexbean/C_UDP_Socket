#define MYPORT 32815
#define BUFFSIZE 1024
struct Data{
    short start;
    char Id;
    short type;
    char segNo;
    char length;
    char payload[255];
    short end;
};

struct Ack{
    short start;
    char Id;
    short type;
    char segNo;
    short end;
};

struct Reject{
    short start;
    char Id;
    short type;
    short rejectCode;
    char segNo;
    short end;
};
