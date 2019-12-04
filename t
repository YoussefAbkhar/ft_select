

while (*head)
{
    ft_putstr_fd((*head)->content,g_data.fd);
    (*head) = (*head)->next;
}