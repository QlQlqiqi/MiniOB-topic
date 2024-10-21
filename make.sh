if [ "$1" = "all" ]; then
    pushd src/observer/sql/parser/
    ./gen_parser.sh
    popd
else
    echo "1"
fi


./build.sh debug --make -j24