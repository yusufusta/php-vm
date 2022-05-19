#pragma once

extern "C" {
    #include "sapi/embed/php_embed.h"
}

#define EXTERNC extern "C"

namespace php {
class VM {
  public:
    VM(int argc, char **argv) {
        php_embed_init(argc, argv);
        exit_status = 0;
        program_name = argv[0];
    }
    ~VM() {
        php_embed_shutdown();
    }
    void eval(const char *script) {
        std::string s(script);
        eval(s);
    }
    void eval(std::string &script) {
        zend_first_try {
            zend_eval_stringl((char *) script.c_str(), script.length(), NULL, (char *) program_name.c_str());
        }
        zend_catch {
            exit_status = EG(exit_status);
        }
        zend_end_try();
    }
    int exit_status;

  private:
    std::string program_name;
};
}

int main(int argc, char *argv[]) {
    php::VM vm(argc, argv);
    vm.eval("echo 'Hello World!';");
    return 0;
}