import { Component } from '@angular/core';
import { CommonModule } from '@angular/common';
import { FormsModule } from '@angular/forms';
import { Router } from '@angular/router';
import { AuthService } from '../../services/auth.service';

@Component({
  selector: 'app-login',
  standalone: true,
  imports: [CommonModule, FormsModule],
  templateUrl: './login.component.html',
  styleUrls: ['./login.component.scss']
})
export class LoginComponent {
  username: string = '';
  password: string = '';
  errorMessage: string = '';
  isLoading: boolean = false;

  constructor(private authService: AuthService, private router: Router) {
    // Ako je već prijavljen, preusmeri na passwords stranicu
    if (this.authService.isAuthenticated()) {
      this.router.navigate(['/passwords']);
    }
  }

  login(): void {
    this.errorMessage = '';
    this.isLoading = true;

    if (!this.username || !this.password) {
      this.errorMessage = 'Molimo unesite korisničko ime i lozinku';
      this.isLoading = false;
      return;
    }

    this.authService.login(this.username, this.password).subscribe({
      next: (body: Object) => {
        const status = body as any;
        if (status.login == 'success') {
          this.authService.storeCredentials(this.username, this.password);
          this.router.navigate(['/passwords']);
          this.isLoading = false;
        } else {
          this.isLoading = false;
          this.password = '';
          this.errorMessage = 'Neispravno korisničko ime ili lozinka';
        }
      },
      error: (error) => {
        this.isLoading = false;
        this.errorMessage = 'Greška prilikom prijave. Molimo pokušajte ponovo.';
        this.password = '';
        console.error('Login error:', error);
      }
    });
  }
}
