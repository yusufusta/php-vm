PHP_INCLUDE = `php-config --includes`
PHP_LIBS = `php-config --libs`
PHP_LDFLAGS = `php-config --ldflags`
PHP_INCLUDE_DIR = `php-config --include-dir`
PHP_EXTENSION_DIR = `php-config --extension-dir`

embed: init.cpp
	c++ -DHAVE_CONFIG_H -g -o embed -O0 init.cpp -fPIC `php-config --includes` -I`php-config --include-dir` `php-config --ldflags` `php-config --libs` -lphp
clean:
	rm embed
