#!/usr/bin/env bash
for f in $@; do
	./run.sh $f
	sleep 0.33
done
