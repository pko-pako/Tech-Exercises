# Define parameters
param (
    [int]$prNumber
)

# Change to the repository directory (assumed to be the current location)
Set-Location -Path './'

# Check if user is logged into github
if (-not gh auth status --hostname "github.com"){
	Write-Host "You're not authenticated, please login following the steps.`nIf you choose not to use credentials, mobile app authentication will be used."
	gh auth login --git-protocol HTTPS --hostname "github.com" --web
}

# Get the original pull request details
$sourcePr = gh pr view $prNumber --json headRefName,title,body | ConvertFrom-Json
$sourceBranch = $sourcePr.headRefName
$sourcePrTitle = $sourcePr.title
$sourcePrBody = $sourcePr.body

# Check if the name of the branch starts with "dependabot/"
$requiredPrefix = "dependabot/"
if (-not ($sourceBranch.StartsWith($requiredPrefix))) {
    Write-Host "PR branch does not start with '$requiredPrefix'. Exiting script."
    exit
}

$newBranch = "scripted/" + $sourceBranch

# Pull the latest changes from the source branch
git checkout $sourceBranch
git pull origin $sourceBranch

# Create and switch to the new branch
git checkout -b $newBranch

# Merge changes from the source branch to the new branch
git merge $sourceBranch

# Push the new branch to the origin
git push -u origin $newBranch

# Create a new pull request for the new branch with the same title and body as the original
$newPrUrl = gh pr create --title "$sourcePrTitle" --body "$sourcePrBody" --base main --head $newBranch --repo "milestone-systems-as/DeviceIntegrationServices"

# Close the original pull request
gh pr close $prNumber

# Output the URL of the new pull request
Write-Output "New pull request created: $newPrUrl"

# Open the url of the pull request
Start-Process $newPrUrl
