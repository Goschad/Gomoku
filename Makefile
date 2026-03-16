NAME = gomoku

CXX = c++
CXXFLAGS = -Wall -Wextra -Werror -std=c++17

SRCDIR = src
SRC = $(SRCDIR)/main.cpp \
	  $(SRCDIR)/render/Renderer.cpp \
	  $(SRCDIR)/core/Board.cpp

OBJ = $(SRC:.cpp=.o)

INCLUDE_DIR = include
SFML_DIR = SFML
SFML_BUILD = $(SFML_DIR)/build
SFML_INSTALL = $(CURDIR)/sfml-install

INCLUDES = -I$(SFML_INSTALL)/include
LIBS = -L$(SFML_INSTALL)/lib -lsfml-graphics -lsfml-window -lsfml-system
RPATH = -Wl,-rpath,$(SFML_INSTALL)/lib

all: sfml $(NAME)

$(NAME): $(OBJ)
	$(CXX) $(CXXFLAGS) $(OBJ) -o $(NAME) $(LIBS) $(RPATH)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) $(INCLUDES) -c $< -o $@

sfml:
	@if [ ! -d "$(SFML_DIR)" ]; then \
		git clone https://github.com/SFML/SFML.git; \
	fi
	@mkdir -p $(SFML_BUILD)
	@cd $(SFML_BUILD) && env -u LDFLAGS -u CPPFLAGS -u CFLAGS -u CXXFLAGS cmake .. \
		-DCMAKE_INSTALL_PREFIX=$(SFML_INSTALL) \
		-DBUILD_SHARED_LIBS=ON \
		-DSFML_BUILD_FRAMEWORKS=OFF
	@env -u LDFLAGS -u CPPFLAGS -u CFLAGS -u CXXFLAGS cmake --build $(SFML_BUILD) -j4
	@env -u LDFLAGS -u CPPFLAGS -u CFLAGS -u CXXFLAGS cmake --install $(SFML_BUILD)

clean:
	rm -f $(OBJ)

fclean: clean
	rm -f $(NAME)
	rm -rf $(SFML_BUILD)
	rm -rf $(SFML_INSTALL)

distclean: fclean
	rm -rf $(SFML_DIR)

re: distclean all

.PHONY: all clean fclean distclean re