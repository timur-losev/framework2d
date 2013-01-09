// Test.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "SignalsBase.h"


static boost::condition_variable cond;
static bool ready = false;

static boost::mutex mutex;
static boost::mutex logmutex;

static std::queue<int> messages;

class LogSink: public boost::iostreams::sink
{
public:
    std::streamsize write(const char* s, std::streamsize n)
    {
        boost::mutex::scoped_lock lock(logmutex);

        boost::container::string str(s, n);
        std::cout << boost::this_thread::get_id() << ": " << str;
        std::flush(std::cout);

        return n;
    }
} sink;

static boost::iostreams::stream_buffer<LogSink> logbuf(sink, 50000);
static std::ostream out(&logbuf);

static void consume()
{
    while(true)
    {
        boost::mutex::scoped_lock lock(mutex);

        if(messages.empty())
        {
            out << "Waiting..." << std::endl;
            cond.wait(lock);
        }

        out << "Got " << messages.front() << std::endl;
        messages.pop();
    }
}

static void produce()
{
    int i = 0;

    while(true)
    {
        boost::mutex::scoped_lock lock(mutex);

        messages.push(i);
        ++i;

        cond.notify_one();
    }
}

struct TestClass
{
    void Somefunc1(int a, std::vector<float> b)
    {

    }

    void Somefunc2(float* a, const std::string& str)
    {

    }
};

int _tmain(int argc, _TCHAR* argv[])
{
    out << "Start" << std::endl;

#if 0
    boost::thread t(produce);

    boost::thread t2(consume);

    while(true)
    {
        boost::this_thread::sleep(boost::posix_time::seconds(1));
    }

#endif

    TestClass *testClass = new TestClass();

    std::vector<float> b;
    b.push_back(10.8f);
    b.push_back(10.9f);
    b.push_back(10.12f);

    SignalsBase base;

    base.AttachOn<int, std::vector<float>>("Somefunc1", boost::bind(&TestClass::Somefunc1, testClass, _1, _2));

    base.DoVoidCall("Somefunc1", 10, b);

	return 0;
}

