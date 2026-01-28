import { Component, Input, Output, EventEmitter, inject } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { Account } from '../../models/account';
import { AccountService } from '../../services/account.service';

@Component({
  selector: 'app-account-detail-modal',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './account-detail-modal.component.html',
  styleUrls: ['./account-detail-modal.component.scss']
})
export class AccountDetailModalComponent {
  @Input() account!: Account;
  @Output() close = new EventEmitter<void>();
  @Output() update = new EventEmitter<Account>();
  @Output() delete = new EventEmitter<number>();

  isEditing: boolean = false;
  editedAccount: Account = {
    service: '',
    username: '',
    password: ''
  };
  showPassword: boolean = false;
  showConfirmDelete: boolean = false;

  private accountService = inject(AccountService);

  ngOnInit(): void {
    this.editedAccount = { ...this.account };
  }

  toggleEdit(): void {
    if (this.isEditing) {
      this.editedAccount = { ...this.account };
    }
    this.isEditing = !this.isEditing;
  }

  togglePasswordVisibility(): void {
    this.showPassword = !this.showPassword;
  }

  copyToClipboard(text: string): void {
    navigator.clipboard.writeText(text).then(() => {
      alert('Kopijano u privremenu memoriju!');
    });
  }

  saveChanges(): void {
    this.accountService.updateAccount(this.editedAccount).subscribe(() => {
      console.log('Edited account', this.editedAccount);
      window.location.reload();
    });
  }

  toggleConfirmDelete(): void {
    this.showConfirmDelete = !this.showConfirmDelete;
  }

  onBackdropClick(event: MouseEvent): void {
    if (event.target === event.currentTarget) {
      this.close.emit();
    }
  }
}
