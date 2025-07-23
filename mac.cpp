#ifdef __APPLE__

typedef struct
{
    pthread_mutex_t mutex;
    pthread_cond_t  cond;
    unsigned count;
}
bosal_sem_t;

int sem_init(sem_t *psem, int flags, unsigned count)
{
    bosal_sem_t *pnewsem;
    int result;

    pnewsem = (bosal_sem_t *)malloc(sizeof(bosal_sem_t));
    if (! pnewsem)
    {
        return -1;
    }
    result = pthread_mutex_init(&pnewsem->mutex, NULL);
    if (result)
    {
        free(pnewsem);
        return result;
    }
    result = pthread_cond_init(&pnewsem->cond, NULL);
    if (result)
    {
        pthread_mutex_destroy(&pnewsem->mutex);
        free(pnewsem);
        return result;
    }
    pnewsem->count = count;
    *psem = (sem_t)pnewsem;
    return 0;
}

int sem_destroy(sem_t *psem)
{
    bosal_sem_t *poldsem;

    if (! psem)
    {
        return EINVAL;
    }
    poldsem = (bosal_sem_t *)*psem;

    pthread_mutex_destroy(&poldsem->mutex);
    pthread_cond_destroy(&poldsem->cond);
    free(poldsem);
    return 0;
}

int sem_post(sem_t *psem)
{
     bosal_sem_t *pxsem;
    int result, xresult;

    if (! psem)
    {
        return EINVAL;
    }
    pxsem = (bosal_sem_t *)*psem;

    result = pthread_mutex_lock(&pxsem->mutex);
    if (result)
    {
        return result;
    }
    pxsem->count = pxsem->count + 1;

    xresult = pthread_cond_signal(&pxsem->cond);

    result = pthread_mutex_unlock(&pxsem->mutex);
    if (result)
    {
        return result;
    }
    if (xresult)
    {
        errno = xresult;
        return -1;
    }
}

int sem_trywait(sem_t *psem)
{
    bosal_sem_t *pxsem;
    int result, xresult;

    if (! psem)
    {
        return EINVAL;
    }
    pxsem = (bosal_sem_t *)*psem;

    result = pthread_mutex_lock(&pxsem->mutex);
    if (result)
    {
        return result;
    }
    xresult = 0;

    if (pxsem->count > 0)
    {
        pxsem->count--;
    }
    else
    {
        xresult = EAGAIN;
    }
    result = pthread_mutex_unlock(&pxsem->mutex);
    if (result)
    {
        return result;
    }
    if (xresult)
    {
        errno = xresult;
        return -1;
    }
    return 0;
}

int sem_wait(sem_t *psem)
{
    bosal_sem_t *pxsem;
    int result, xresult;

    if (! psem)
    {
        return EINVAL;
    }
    pxsem = (bosal_sem_t *)*psem;

    result = pthread_mutex_lock(&pxsem->mutex);
    if (result)
    {
        return result;
    }
    xresult = 0;

    if (pxsem->count == 0)
    {
        xresult = pthread_cond_wait(&pxsem->cond, &pxsem->mutex);
    }
    if (! xresult)
    {
        if (pxsem->count > 0)
        {
            pxsem->count--;
        }
    }
    result = pthread_mutex_unlock(&pxsem->mutex);
    if (result)
    {
        return result;
    }
    if (xresult)
    {
        errno = xresult;
        return -1;
    }
    return 0;
}

int sem_timedwait(sem_t *psem, const struct timespec *abstim)
{
    bosal_sem_t *pxsem;
    int result, xresult;

    if (! psem)
    {
        return EINVAL;
    }
    pxsem = (bosal_sem_t *)*psem;

    result = pthread_mutex_lock(&pxsem->mutex);
    if (result)
    {
        return result;
    }
    xresult = 0;

    if (pxsem->count == 0)
    {
        xresult = pthread_cond_timedwait(&pxsem->cond, &pxsem->mutex, abstim);
    }
    if (! xresult)
    {
        if (pxsem->count > 0)
        {
            pxsem->count--;
        }
    }
    result = pthread_mutex_unlock(&pxsem->mutex);
    if (result)
    {
        return result;
    }
    if (xresult)
    {
        errno = xresult;
        return -1;
    }
    return 0;
}

#endif