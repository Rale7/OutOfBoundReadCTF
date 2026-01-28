import { HttpInterceptorFn } from '@angular/common/http';
import { inject } from '@angular/core';
import { AuthService } from '../services/auth.service';

export const authInterceptor: HttpInterceptorFn = (req, next) => {
  const authService = inject(AuthService);
  const credentials = authService.getStoredCredentials();

  console.log('AuthInterceptor - URL:', req.url, 'Has credentials:', !!credentials);

  if (credentials && !req.url.includes('/login')) {
    const basicAuth = btoa(`${credentials.username}:${credentials.password}`);
    console.log('AuthInterceptor - Adding Basic Auth header');

    const authReq = req.clone({
      setHeaders: {
        Authorization: `Basic ${basicAuth}`
      }
    });
    return next(authReq);
  }

  console.log('AuthInterceptor - No auth header added');
  return next(req);
};