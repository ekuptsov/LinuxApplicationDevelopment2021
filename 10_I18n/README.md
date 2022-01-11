Build and install
-----------------
```sh
meson setup builddir
cd builddir
ninja
```

Run w/ locale (only Russian)
-----------------
```sh
LC_ALL=ru_RU.UTF8 ./binsearch
```

Add new language
-----------------
1. Append lang in po/LINGUAS
2. Create ./po/your-language.po (change CHARSET to UTF-8 if needed)
```sh
cd builddir
meson compile binsearch-update-po
```
3. Fill ./po/your-language.po translation
4. Compile it
```sh
meson compile binsearch-gmo
```
5. Run
```sh
LC_ALL=your-locale ./binsearch
```