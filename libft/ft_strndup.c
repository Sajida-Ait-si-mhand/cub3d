
#include "libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t	len;
	char	*new_str;

	if (s == NULL)
		return (NULL);
	len = 0;
	while (len < n && s[len] != '\0')
		len++;
	new_str = (char *)malloc(len + 1);
	if (new_str == NULL)
		return (NULL);
	ft_memcpy(new_str, s, len);
	new_str[len] = '\0';
	return (new_str);
}
