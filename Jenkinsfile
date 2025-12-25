pipeline {
    agent any

    environment {
        ALLURE_RESULTS = 'allure-results'
        ALLURE_REPORT = 'allure-report'
    }

    stages {
        stage('Checkout') {
            steps {
                checkout scm
            }
        }

        stage('Restore') {
            steps {
                script {
                    dir('DemoAllureProject.Tests') {
                        sh '/usr/bin/dotnet restore'
                    }
                }
            }
        }

        stage('Build') {
            steps {
                script {
                    dir('DemoAllureProject.Tests') {
                        sh '/usr/bin/dotnet build --no-restore'
                    }
                }
            }
        }

        stage('Test') {
            steps {
                script {
                    dir('DemoAllureProject.Tests') {
                        // Run tests and generate Allure results
                        // Allure results are generated in bin/Debug/net8.0/allure-results by default
                        sh '''
                            /usr/bin/dotnet test --no-build --verbosity normal \
                                --logger "trx;LogFileName=test-results.trx"
                        '''
                        // Copy Allure results to project root for easier access
                        sh '''
                            if [ -d "bin/Debug/net8.0/allure-results" ]; then
                                mkdir -p allure-results
                                cp -r bin/Debug/net8.0/allure-results/* allure-results/ || true
                            fi
                        '''
                    }
                }
            }
        }

        stage('Generate Allure Report') {
            steps {
                script {
                    dir('DemoAllureProject.Tests') {
                        // Generate Allure report from results
                        sh '''
                            if [ -d "allure-results" ] && [ "$(ls -A allure-results)" ]; then
                                allure generate allure-results -o allure-report --clean
                            elif [ -d "bin/Debug/net8.0/allure-results" ] && [ "$(ls -A bin/Debug/net8.0/allure-results)" ]; then
                                allure generate bin/Debug/net8.0/allure-results -o allure-report --clean
                            else
                                echo "No allure-results directory found"
                            fi
                        '''
                    }
                }
            }
        }
    }

    post {
        always {
                script {
                    dir('DemoAllureProject.Tests') {
                        // Publish Allure report
                        // Try allure-results first, fallback to bin directory
                        def resultsPath = fileExists('allure-results') ? 'allure-results' : 'bin/Debug/net8.0/allure-results'
                        allure([
                            includeProperties: false,
                            jdk: '',
                            properties: [],
                            reportBuildPolicy: 'ALWAYS',
                            results: [[path: resultsPath]]
                        ])
                    }
                }
        }
        success {
            echo 'Pipeline succeeded!'
        }
        failure {
            echo 'Pipeline failed!'
        }
    }
}

