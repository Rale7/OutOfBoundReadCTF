import { HttpClient } from '@angular/common/http';
import { inject, Injectable } from '@angular/core';
import { BehaviorSubject, Observable, catchError, map, of } from 'rxjs';

interface LoginCredentials {
  username: string;
  password: string;
}

@Injectable({
  providedIn: 'root'
})
export class AuthService {
  private isAuthenticatedSubject = new BehaviorSubject<boolean>(false);
  public isAuthenticated$ = this.isAuthenticatedSubject.asObservable();

  private url = 'http://localhost:8080/login';
  private httpClient = inject(HttpClient);

  constructor() {
    // Proverava da li je korisnik već prijavljen
    const storedCredentials = this.getStoredCredentials();
    if (storedCredentials) {
      this.isAuthenticatedSubject.next(true);
    }
  }

  login(username: string, password: string) {
    const basicAuth = btoa(`${username}:${password}`);

    return this.httpClient.post<Object>(this.url, {
      "username": username,
      "password": password
    })
  }

  logout(): void {
    this.isAuthenticatedSubject.next(false);
    localStorage.removeItem('auth_credentials');
    localStorage.removeItem('user');
  }

  isAuthenticated(): boolean {
    const isAuth = this.isAuthenticatedSubject.value;
    console.log('AuthService - isAuthenticated:', isAuth);
    return isAuth;
  }

  getUser(): string | null {
    const credentials = this.getStoredCredentials();
    return credentials ? credentials.username : null;
  }

  getStoredCredentials(): LoginCredentials | null {
    const stored = localStorage.getItem('auth_credentials');
    console.log('AuthService - getStoredCredentials, stored:', stored);

    if (stored) {
      try {
        const credentials = JSON.parse(stored);
        console.log('AuthService - parsed credentials:', credentials);
        return credentials;
      } catch (e) {
        console.error('Error parsing stored credentials:', e);
        return null;
      }
    }
    return null;
  }

  storeCredentials(username: string, password: string): void {
    const credentials: LoginCredentials = { username, password };
    localStorage.setItem('auth_credentials', JSON.stringify(credentials));
    localStorage.setItem('user', username);
    this.isAuthenticatedSubject.next(true);
  }

  setAuthenticated(authenticated: boolean): void {
    this.isAuthenticatedSubject.next(authenticated);
  }
}
