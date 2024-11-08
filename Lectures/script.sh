for i in {1..15}; do echo "Line $i" >> foo.txt ; done
for i in {4..7}; do awk NR==$i foo.txt; done
