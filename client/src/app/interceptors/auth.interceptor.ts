import { Injectable } from '@angular/core';
import { HttpInterceptor, HttpRequest, HttpHandler, HttpEvent } from '@angular/common/http';
import { Observable } from 'rxjs';
import { AuthService } from '../services/auth.service';

@Injectable()
export class AuthInterceptor implements HttpInterceptor {
  constructor(private authService: AuthService) { }

  intercept(req: HttpRequest<any>, next: HttpHandler): Observable<HttpEvent<any>> {
    const credentials = this.authService.getStoredCredentials();

    if (credentials && !req.url.includes('/login')) {
      const basicAuth = btoa(`${credentials.username}:${credentials.password}`);
      const authReq = req.clone({
        setHeaders: {
          Authorization: `Basic ${basicAuth}`
        }
      });
      return next.handle(authReq);
    }

    return next.handle(req);
  }
}