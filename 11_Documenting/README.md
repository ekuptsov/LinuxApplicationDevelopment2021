Build and install
-----------------
```sh
meson setup builddir
cd builddir
ninja
```

Documentation
```sh
ninja docs
```

Manpage generated automatically
```sh
help2man -N ./roman_binsearch -o roman_binsearch.man
man -l roman_binsearch.man
```

Run w/ locale (only Russian)
-----------------
```sh
LC_ALL=ru_RU.UTF8 ./roman_binsearch
```

Add new language
-----------------
1. Append lang in po/LINGUAS
2. Create ./po/your-language.po (change CHARSET to UTF-8 if needed)
```sh
cd builddir
meson compile roman_binsearch-update-po
```
3. Fill ./po/your-language.po translation
4. Compile it
```sh
meson compile roman_binsearch-gmo
```
5. Run
```sh
LC_ALL=your-locale ./roman_binsearch
```