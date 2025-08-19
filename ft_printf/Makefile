
NAME	= libftprintf.a
SRCDIR	= ./srcs
OBJDIR	= ./objs
#BONUSDIR	= .
SRCS	+= $(SRCDIR)/ft_printf_utils.c
SRCS	+= $(SRCDIR)/ft_printf.c
SRCS	+= $(SRCDIR)/ft_putchar.c
SRCS	+= $(SRCDIR)/ft_putnbr_base.c
SRCS	+= $(SRCDIR)/ft_putnbr_decimal.c
SRCS	+= $(SRCDIR)/ft_putnbr_ptr.c
SRCS	+= $(SRCDIR)/ft_putnbr_ul_base16.c
SRCS	+= $(SRCDIR)/ft_putstr.c
OBJS	= $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)
#BOBJS	= $(BONUS:$(BONUSDIR)/%.c=$(BONUSDIR)/%.o)

CC		= cc
CFLAGS	= -Wall -Wextra -Werror -Iincludes
AR		= ar
ARFLAGS	= rcs

all: $(OBJDIR) $(NAME)

$(OBJDIR):
	mkdir -p $(OBJDIR)
	
$(NAME):	$(OBJS)
	$(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(OBJDIR)/%.o: $(SRCDIR)/%.c
	$(CC) $(CFLAGS) -c $< -o $@

#bonus: $(OBJS) $(BOBJS)
#$(AR) $(ARFLAGS) $(NAME) $(OBJS) $(BOBJS)

#$(BONUSDIR)/%.o: $(BONUSDIR)/%.c
#$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f $(OBJS) $(BOBJS)

fclean: clean
	rm -f $(NAME)

re:	fclean all# bonus

.PHONY: all clean fclean re bonus
