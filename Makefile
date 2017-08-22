app:
	@cd app/
	$(MAKE)

run: app
	@cd ..
	build/app/App

compile:
	cd build/
	$(MAKE)

