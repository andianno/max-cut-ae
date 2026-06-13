# Definiamo il compilatore e i flag di ottimizzazione
CXX = g++
CXXFLAGS = -O3 -std=c++11 -Wall

# I nomi dei programmi finali che vogliamo creare (aggiunto test_generators)
TARGETS = run_nphard run_experiments run_experiments_d test_generators

# I "pezzi di motore" condivisi da tutti i programmi
OBJS = src/utils.o src/randomized.o src/greedy.o src/exact.o

# Regola principale: quando scrivi "make", compila tutti i target
all: $(TARGETS)

# 1. Come costruire l'esperimento sui grafi piccoli (NP-Hardness)
run_nphard: src/main_nphard.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 2. Come costruire l'esperimento principale (Big Data)
run_experiments: src/main_exp.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 3. Come costruire l'esperimento con step logaritmici (Doubling)
run_experiments_d: src/main_exp_d.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# 4. Come costruire i test dei generatori di grafi
test_generators: src/test_generators.o $(OBJS)
	$(CXX) $(CXXFLAGS) -o $@ $^

# Regola magica: insegna al Makefile come trasformare QUALSIASI .cpp in un .o
src/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

# Regola per pulire la cartella dai file compilati
clean:
	rm -f src/*.o $(TARGETS)