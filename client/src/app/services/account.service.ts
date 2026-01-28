import { inject, Injectable } from '@angular/core';
import { BehaviorSubject, Observable } from 'rxjs';
import { Account } from '../models/account';
import { HttpClient } from '@angular/common/http';

@Injectable({
  providedIn: 'root'
})
export class AccountService {

  private httpClient = inject(HttpClient);

  constructor() { }

  getAccounts() {
    const url = 'http://localhost:8080/getAccounts';
    return this.httpClient.get<Account[]>(url);
  }

  getAccountById(id: number) {
    const url = 'http://localhost:8080/getAccountByIndex' + `/${id}`;
    return this.httpClient.get<Account[]>(url);
  }

  addAccount(account: Account): void {

  }

  updateAccount(account: Account) {
    const url = 'http://localhost:8080/changeAccount';
    return this.httpClient.post<Account>(url, account);
  }

  deleteAccount(id: number): void {

  }

  exportToFile(size: number) {
    const url = `http://localhost:8080/exportFromFile/${size}`;
    return this.httpClient.get(url, { responseType: 'text' });
  }

  importFromText(text: string) {
    const url = 'http://localhost:8080/importToFile';
    return this.httpClient.post(url, text, {
      headers: { 'Content-Type': 'text/plain' },
      responseType: 'text'
    });
  }


}
