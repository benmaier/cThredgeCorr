default:
	make python

clean:
	-rm -f *.o
	-rm -f $(TARGET)

clean_all:
	make clean
	make pyclean

pyclean:
	-rm -f *.so
	-rm -rf *.egg-info*
	-rm -rf ./tmp/
	-rm -rf ./build/

python:
	make pyclean
	pip install -e ../cThredgeCorr --no-binary :all:
