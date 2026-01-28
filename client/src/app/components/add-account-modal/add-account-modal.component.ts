import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { Account } from '../../models/account';
import { Output, EventEmitter } from '@angular/core';

@Component({
  selector: 'app-add-account-modal',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './add-account-modal.component.html',
  styleUrls: ['./add-account-modal.component.scss']
})
export class AddAccountModalComponent {
  @Output() close = new EventEmitter<void>();
  @Output() save = new EventEmitter<Account>();

  newAccount: Account = {
    service: '',
    username: '',
    password: '',
  };

  validationErrors: string[] = [];

  addAccount(): void {
    this.validationErrors = [];

    if (!this.newAccount.service?.trim()) {
      this.validationErrors.push('Servis je obavezan');
    }
    if (!this.newAccount.username?.trim()) {
      this.validationErrors.push('Korisničko ime je obavezno');
    }
    if (!this.newAccount.password?.trim()) {
      this.validationErrors.push('Lozinka je obavezna');
    }

    if (this.validationErrors.length === 0) {
      this.save.emit(this.newAccount);
    }
  }

  onBackdropClick(event: MouseEvent): void {
    if (event.target === event.currentTarget) {
      this.close.emit();
    }
  }
}
