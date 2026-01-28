import { Component, OnInit } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { Router } from '@angular/router';
import { AccountService } from '../../services/account.service';
import { AuthService } from '../../services/auth.service';
import { Account } from '../../models/account';
import { AccountDetailModalComponent } from '../account-detail-modal/account-detail-modal.component';
import { HttpClient } from '@angular/common/http';

@Component({
  selector: 'app-passwords',
  standalone: true,
  imports: [CommonModule, FormsModule, AccountDetailModalComponent],
  templateUrl: './passwords.component.html',
  styleUrls: ['./passwords.component.scss']
})
export class PasswordsComponent implements OnInit {
  accounts: Account[] = [];
  filteredAccounts: Account[] = [];
  searchTerm: string = '';
  selectedAccount: Account | null = null;
  showDetailModal: boolean = false;
  showImportModal: boolean = false;
  importText: string = '';

  constructor(
    private accountService: AccountService,
    private authService: AuthService,
    private router: Router,
    private http: HttpClient
  ) { }

  ngOnInit(): void {
    this.accountService.getAccounts().subscribe(accounts => {
      this.accounts = accounts;
    });
  }


  search(): void {
    if (this.searchTerm && !isNaN(Number(this.searchTerm))) {
      const id = Number(this.searchTerm);
      console.log('Searching for account with ID:', id);
      this.accountService.getAccountById(id).subscribe(accounts => {
        this.accounts = accounts;
      });
    }
  }

  openDetailModal(account: Account): void {
    this.selectedAccount = { ...account };
    this.showDetailModal = true;
  }

  closeDetailModal(): void {
    this.showDetailModal = false;
    this.selectedAccount = null;
  }

  onAccountUpdated(account: Account): void {
    this.accountService.updateAccount(account);
    this.closeDetailModal();
  }

  exportToFile(): void {
    const maxSize = prompt('Unesite maksimalnu veličinu fajla (u B):');

    if (!maxSize || isNaN(Number(maxSize))) {
      alert('Molimo unesite validnu brojnu vrednost za veličinu fajla');
      return;
    }

    this.accountService.exportToFile(Number(maxSize)).subscribe({
      next: (data: string) => {
        const filename = 'exported_accounts.txt';
        this.downloadFile(data, filename);
      },
      error: (error) => {
        console.error('Greška prilikom izvoza fajla:', error);
        alert('Došlo je do greške prilikom izvoza fajla. Molimo pokušajte ponovo.');
      }
    });

  }

  private downloadFile(content: string, filename: string): void {
    const blob = new Blob([content], { type: 'text/plain' });
    const url = window.URL.createObjectURL(blob);
    const link = document.createElement('a');
    link.href = url;
    link.download = filename;
    document.body.appendChild(link);
    link.click();
    document.body.removeChild(link);
    window.URL.revokeObjectURL(url);
  }

  openImportModal(): void {
    this.showImportModal = true;
    this.importText = '';
  }

  closeImportModal(): void {
    this.showImportModal = false;
    this.importText = '';
  }

  sendImportData(): void {
    if (!this.importText.trim()) {
      alert('Molimo unesite tekst za import');
      return;
    }

    this.accountService.importFromText(this.importText).subscribe({
      next: (response) => {
        console.log('Import uspešan:', response);
        alert('Podaci su uspešno importovani!');
        this.closeImportModal();
        // Refresh accounts list
        this.accountService.getAccounts().subscribe(accounts => {
          this.accounts = accounts;
        });
      },
      error: (error) => {
        console.error('Greška prilikom importa:', error);
        alert('Došlo je do greške prilikom importa. Molimo pokušajte ponovo.');
      }
    });
  }

  logout(): void {
    this.authService.logout();
    this.router.navigate(['/login']);
  }

  indexOf(account: Account): number {
    return this.accounts.findIndex(a => a === account);
  }
}
