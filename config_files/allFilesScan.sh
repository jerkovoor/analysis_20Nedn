numFiles=(
11
13
9
1
1
2
3
6
1
1
2
1
9
1
1
10
11
4
3
1
7
7
8
9
1
2
5
1
14
5
12
1
10
10
10
10
10
11
10
10
9
9
1
2
13
1
2
1
7
10
4
1
11
2
6
)


for i in {14..55}; do
	./multiscan.sh "run_0$i" "run$i" Config_11Mods_labr_stb_EBIT.xml ${numFiles[i-1]}
done
