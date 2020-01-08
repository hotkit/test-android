#include <jni.h>
#include <messaging.hpp>

#include <fost/insert>
#include <fost/test>
#include <thread>


namespace {
    const fostlib::setting<bool> c_verbose(
            "native-lib.cpp",
            "Tests", "Display test names", true);
}


extern "C" JNIEXPORT void JNICALL
Java_com_felspar_android_fosttester_Tester_runTests(
        JNIEnv *env, jobject /* this */
) {
    std::thread tests{[]() {
        std::stringstream ss;
        try {
            fostlib::test::suite::execute(ss);
        } catch (std::exception &e) {
            ss << e.what() << '\n';
        }
        fostlib::json msg;
        insert(msg, "display", fostlib::string{ss.str()});
        send_message(msg);
    }};
    tests.detach();
}

