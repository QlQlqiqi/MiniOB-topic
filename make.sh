if [ "$1" = "all" ]; then
    pushd src/observer/sql/parser/
    ./gen_parser.sh
    popd
fi


./build.sh debug --make -j24
