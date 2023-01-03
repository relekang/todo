default: $(HOME)/.local/bin/todo $(HOME)/Library/Application\ Support/xbar/plugins/todo.10s.sh

GO_FILES := $(shell find . -name '*.go')

todo: $(GO_FILES)
		go build

$(HOME)/.local/bin/todo: todo
		install -m 755 todo $(HOME)/.local/bin/todo

$(HOME)/Library/Application\ Support/xbar/plugins/todo.10s.sh:
	ln -s $(PWD)/xbar.sh $(HOME)/Library/Application\ Support/xbar/plugins/todo.10s.sh

readme.md: todo
	echo "# todo" > readme.md
	echo "" >> readme.md
	echo '```' >> readme.md
	./todo -h >> readme.md
	echo '```' >> readme.md

.PHONY: default
