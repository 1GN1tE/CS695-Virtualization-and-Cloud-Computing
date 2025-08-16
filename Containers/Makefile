# Makefile for assignment #3

HOSTIP:= 10.129.135.190

.PHONY: all build clean distclean \
        build-task1 run-task1 \
        build-task2 run-task2 \
        build-task3 run-task3 \
		run-task3a run-task3b \
		run-task3d1 run-task3d2a \
		run-task3d2b run-task3d3 \
		run-task3e stop-task3 build-task4 \
        run-task4 run-test4

all: build

build: build-task1 build-task2 build-task3
	@echo ""
	@echo "✅ All builds completed."
	@echo "👉 You can now run individual tasks with:"
	@echo "   make run-task1, make run-task2"
	@echo "   make run-task3, make run-task4"
	@echo ""

build-task1: task1/namespace_prog.c
	@echo "🔨 Building task1 (namespace_prog.c)..."
	@gcc task1/namespace_prog.c -o task1/namespace_prog

build-task2: task2/container_prog.c task2/simple_container.sh
	@echo "🔨 Building task2 (container_prog.c)..."
	@gcc task2/container_prog.c -o task2/container_prog

build-task3: task3/setup.sh task3/conductor.sh
	@echo "🔨 Debootstrap task3 (conductor.sh)..."
	@if [ -f task3/conductor.sh ]; then \
		if [ -d "task3/.cache/base/debian-bookworm" ]; then \
			echo "🙌 Base image setup already done, skipping debootstrap..."; \
		else \
			cd task3 && bash conductor.sh build test && cd .. ; \
		fi \
	else \
		echo "❌ Error: task3/conductor.sh missing."; \
	fi

build-task4: task4/service-orchestrator.sh task4/counter-service task4/external-service task4/csfile task4/esfile
	@echo "🔨 Building task4/counter-service..."
	@$(MAKE) -C task4/counter-service

run-task1:
	@echo "🚀 Running task1..."
	@if [ -x task1/namespace_prog ]; then \
		sudo ./task1/namespace_prog; \
	else \
		echo "❌ Error: task1/namespace_prog not found. Build it first!"; \
	fi

run-task2:
	@echo "🚀 Running task2..."
	@if [ -x task2/container_prog ] && [ -f task2/simple_container.sh ]; then \
		cd task2 && bash simple_container.sh; \
	else \
		echo "❌ Error: task2 artifacts missing. Build it first!"; \
	fi

run-task3:
	@if [ -f task3/conductor.sh ]; then \
		echo "👣 Task3 has multiple subtasks..."; \
		echo "Start with task3a..."; \
		echo "Check rubric for more instructions."; \
	else \
		echo "❌ Error: task3/conductor.sh missing."; \
	fi

run-subtask3a:
	@echo "🚀 Running task3a..."
	@if [ -f task3/conductor.sh ]; then \
		cd task3 && bash conductor.sh build test1 ; \
		bash conductor.sh images; \
		bash conductor.sh ps ; \
		bash conductor.sh run test1 eg1; \
	else \
		echo "❌ Error: task3/conductor.sh missing."; \
	fi

run-task3b:
	@echo "🚀 Running task3b..."
	@if [ -f task3/conductor.sh ]; then \
		cd task3 && bash conductor.sh ps ; \
		bash conductor.sh exec eg1 /bin/bash; \
	else \
		echo "❌ Error: task3/conductor.sh missing."; \
	fi

run-task3c:
	@echo "🚀 Running task3c..."
	@if [ -f task3/conductor.sh ]; then \
		cd task3; \
		if [ -d ".containers/eg1" ]; then \
			bash conductor.sh addnetwork eg1; \
			ip a; \
			sudo tcpdump -i eg1-outside icmp; \
		else \
			echo "❌ Error: eg1 container not found."; \
		fi; \
	else \
		echo "❌ Error: task3/conductor.sh missing."; \
	fi

run-subtask3da:
	@echo "🚀 Running task3d1..."
	@if [ -f task3/conductor.sh ]; then \
		cd task3 && chmod +x conductor.sh; \
		./conductor.sh build test1 ; \
		./conductor.sh run test1 eg1 ; \
		mount | grep overlay ; \
		sleep 2 ; \
	else \
		echo "❌ Error: task3/conductor.sh missing."; \
	fi

run-subtask3d2a:
	@echo "🚀 Running task3d2a..."
	@if [ -f task3/conductor.sh ]; then \
		cd task3 && chmod +x conductor.sh; \
		./conductor.sh build test1 Testfile1 ; \
		./conductor.sh run test1 eg1 ; \
		mount | grep overlay ; \
		sleep 2 ; \
	else \
		echo "❌ Error: task3/conductor.sh missing."; \
	fi

run-subtask3d2b:
	@echo "🚀 Running task3d2b..."
	@if [ -f task3/conductor.sh ]; then \
		cd task3 && chmod +x conductor.sh; \
		./conductor.sh build test2 Testfile1 ; \
		./conductor.sh run test2 eg2 ; \
		mount | grep overlay ; \
		sleep 2 ; \
	else \
		echo "❌ Error: task3/conductor.sh missing."; \
	fi

run-subtask3d3:
	@echo "🚀 Running task3d3..."
	@if [ -f task3/conductor.sh ]; then \
		cd task3 && chmod +x conductor.sh; \
		./conductor.sh build test1 Testfile2 ; \
		./conductor.sh run test1 eg1 ; \
		mount | grep overlay ; \
		sleep 2 ; \
	else \
		echo "❌ Error: task3/conductor.sh missing."; \
	fi

run-subtask3e:
	@echo "🚀 Running task3d3..."
	@if [ -f task3/conductor.sh ]; then \
		cd task3 && chmod +x conductor.sh; \
		./conductor.sh build test1 Testfile3 ; \
		./conductor.sh run test1 eg1 ; \
		mount | grep overlay ; \
		sleep 2 ; \
	else \
		echo "❌ Error: task3/conductor.sh missing."; \
	fi

stop-task3:
	@echo "🛑 Stopping task3 containers..."
	@if [ -f task3/conductor.sh ]; then \
		cd task3; \
		if [ -d ".containers/eg1" ]; then \
			bash conductor.sh stop eg1; \
		fi; \
		if [ -d ".containers/eg2" ]; then \
			bash conductor.sh stop eg2; \
		fi; \
		if [ -d ".images/test" ]; then \
			bash conductor.sh rmi test; \
		fi; \
		if [ -d ".images/test1" ]; then \
			bash conductor.sh rmi test1; \
		fi; \
		if [ -d ".images/test2" ]; then \
			bash conductor.sh rmi test2; \
		fi; \
		if [ -d ".cache/layers" ]; then \
			rm -rf .cache/layers; \
		fi; \
	else \
		echo "❌ Error: task3/conductor.sh missing."; \
	fi

run-task3a: run-subtask3a stop-task3
	@echo "🙌 Done..."

run-task3d1: run-subtask3da stop-task3
	@echo "🙌 Done..."

run-task3d2a: run-subtask3d2a stop-task3
	@echo "🙌 Done..."

run-task3d2b: run-subtask3d2b stop-task3
	@echo "🙌 Done..."

run-task3d3: run-subtask3d3 stop-task3
	@echo "🙌 Done..."

run-task3e: run-subtask3e stop-task3
	@echo "🙌 Done..."

run-task4:
	@echo "🚀 Running task4 orchestrator..."
	@if [ -f task4/service-orchestrator.sh ]; then \
		cd task4 && bash service-orchestrator.sh; \
	else \
		echo "❌ Error: task4/service-orchestrator.sh missing."; \
	fi

stop-task4:
	@echo "🛑 Stopping task4 containers..."
	@if [ -f task4/conductor.sh ]; then \
		cd task4; \
		if [ -d ".containers/es-cont" ]; then \
			bash conductor.sh stop es-cont; \
		fi; \
		if [ -d ".containers/cs-cont" ]; then \
			bash conductor.sh stop cs-cont; \
		fi; \
		if [ -d ".images/es-image" ]; then \
			bash conductor.sh rmi es-image; \
		fi; \
		if [ -d ".images/cs-image" ]; then \
			bash conductor.sh rmi cs-image; \
		fi; \
		if [ -d ".cache/layers" ]; then \
			rm -rf .cache/layers; \
		fi; \
	else \
		echo "❌ Error: task4/conductor.sh missing."; \
	fi

run-subtest4:
	@echo "🚀 Running test for task4 orchestrator...(test1)"
	@if [ -f task4/conductor.sh ]; then \
		bash task4/conductor.sh ps; \
		echo "🚀 Running test for task4 orchestrator...(test2)" ; \
		cd task4 && bash conductor.sh exec es-cont -- apt install -y curl ; \
		bash conductor.sh exec es-cont curl http://localhost:8080 ; \
		echo "" ; \
		bash conductor.sh exec es-cont curl http://localhost:8080 ; \
		echo "" ; \
		echo "🚀 Running test for task4 orchestrator...(test3)" ; \
		curl http://$(HOSTIP):3000 ; \
		echo "" ; \
		curl http://$(HOSTIP):3000 ; \
		echo "" ; \
		bash conductor.sh exec es-cont curl http://localhost:8080 ; \
		echo "" ; \
		sleep 2 ; \
	else \
		echo "❌ Error: task4/conductor.sh missing."; \
	fi

run-test4: run-subtest4 stop-task4
	@echo "🙌 Done..."

clean: stop-task3 stop-task4
	@echo "🧹 Cleaning build artifacts..."
	@rm -f task1/namespace_prog task2/container_prog
	@$(MAKE) -C task4/counter-service clean
	@echo "✅ Cleanup complete."

distclean: clean
	@echo "🔥 Performing DIST CLEAN (full wipe for the submission)..."
	@rm -rf \
		task1/namespace_prog.c \
		task2/simple_container.sh \
		task2/container_root \
		task3/conductor.sh \
		task4/conductor.sh \
		task4/setup.sh \
		task4/service-orchestrator.sh \
		task4/csfile \
		task4/esfile
	@echo "✅ Project fully cleaned."

