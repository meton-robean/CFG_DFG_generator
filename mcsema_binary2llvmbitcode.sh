gcc ./test.c -o test

sudo mcsema-disass --arch amd64 --os linux --disassembler /home/cmt/Applications/ida-pro/ida-pro/idal64 --binary ./test --entrypoint main --output auth.cfg --log_file ./log

mcsema-lift-4.0 --arch amd64 --os linux --cfg ./auth.cfg --output ./test.bc --explicit_args

echo "Done!"
